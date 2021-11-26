local TAG = '[ZapMusic]'
local rt = require('ZapRuntime')
local ipc = require('po.ipc')

local api = {}
local clientSide = nil

-- client

local cPlayAudio = {
    new = function(self)
      local o = {}
      setmetatable(o, self)
      self.__index = self
      local t = rt:easyBindEntry("zap:ZapMusic", "e_playmusic", "playaudio", "woo")
      if not t then return nil end
      o.tunnel = t
      o.callbacks = {}

      local x = ipc:handleTunnel(t, o, function ()
        LOGD(TAG, "e_playmusic refuse or die")
      end)
      if not x then t:detach() return nil end

      return o
    end,
    ["@onReplySocket"] = function (self, msg)
      local callbackId = msg:popString()
      local f = nil
      if callbackId then 
        f = self.callbacks[callbackId]
        self.callbacks[callbackId] = nil
      end
      if not f then return end
      local socket = msg:popFD()
      f(socket, "")
    end,
    ["@onReplyCall"] = function (self, msg)
      local callbackId = msg:popString()
      local f = nil
      if callbackId then 
        f = self.callbacks[callbackId]
        self.callbacks[callbackId] = nil
      end
      if not f then return end
      local result = msg:popString()
      local reason = msg:popString()
      local bool = false
      if result == "true" then bool = true end
      f(bool, reason)
    end,
    play = function (self, info, cb)    -- info[type = "VOIP", codec = [rate = "48000", channel = "2", format = "S16LE"]]
      LOGD(TAG, "play in>")
      return ipc:sendCall(self.tunnel, ">play", function (pt)
        LOGD("play ipc:sendCall")
        pt:putString(info.type)
        pt:putString(tostring(info.codec.rate))
        pt:putString(tostring(info.codec.channel))
        pt:putString(info.codec.format)
        return true
      end, cb, self.callbacks)
    end,
}

function api:getPlayAudio(handler)
  LOGD(TAG, "api:getPlayAudio")
    if clientSide == nil then
        clientSide = cPlayAudio:new(handler)
    end
    return clientSide
end

local function checkAndReplyCallFailed(self, msg, callbackId)
  if not msg:isMessageError() then return false end
  LOGD(TAG, "server side: ipc message error")
  if callbackId then self:replyCall(callbackId, "false", "bad args") end
  return true
end

-- server
function api:serveClient(t, handler)
  if clientSide then return nil end

  local serving = {
    [">play"] = function (self, msg)
      LOGD(TAG, ">play in>")
      local info = {codec = {}}
      info.type = msg:popString()
      info.codec.rate = msg:popString()
      info.codec.channel = msg:popString()
      info.codec.format = msg:popString()
      local callbackId = msg:popString()
      if not checkAndReplyCallFailed(self, msg, callbackId) then -- no err 
        local socket = handler:onPlay(info)
        if not socket then
          if callbackId then self:replyCall(callbackId, "false", "bad args") end
        end
        if callbackId then self:replySocket(callbackId, socket) end
      end
    end,
    replySocket = function (self, callbackId, socket)
      return ipc:sendMessage(t, "@onReplySocket", function (pt)
        pt:putString(callbackId)
        pt:putFD(socket)
        return true
      end)
    end,
    replyCall = function (self, callbackId, result, reason)
      return ipc:sendMessage(t, "@onReplyCall", function (pt)
        pt:putString(callbackId)
        pt:putString(result)
        pt:putString(reason)
        return true
      end)
    end
  }
  if not ipc:handleTunnel(t, serving) then t:detach() LOGD(TAG, 'handle tunnel failed') return nil end
  return serving
end

return api

local TAG = "[ZapPlayAudio]"
local rt = require("ZapRuntime")
local FD = FD

local api = {}
local PlayAudioInstanceTable = {}

local callback = nil

-- 给需要播放的应用提供通信服务，建立socket pair
-- 提供服务
local sPlayAudio = {
    type = { VOIP = "VOIP", TV = "TV" },
    new = function (self, uri, entry, tunnel)
      local o = {}
      setmetatable(o, self)
      self.__index = self
      o.uri = uri
      o.entry = entry
      local serving = require("ZapMusic"):serveClient(tunnel, o)
      o.serving = serving
      return o
    end,
    onPlay = function (self, info)
      if not info then return nil end
      if not info.type then return nil end
      if not self.type[info.type] then return nil end
      if not info.codec then return nil end
      if not info.codec.rate then return nil end
      if not info.codec.channel then return nil end
      if not info.codec.format then return nil end

      -- create pairs socket
      local t1, t2, b = FD:socketpair()
      if not b then return nil end
      -- add socket to playlist
      -- info.source = t1
      -- local jsonInfo = EncodeJsonString(info)
      -- rt:postFeed('@sound_ctrl', '{"type":"sound_ctrl","action":"play_audio", "info":' .. jsonInfo .. '}')
      if callback then callback(info, t1) end
      -- return socket
      LOGD(TAG, "return socket to client")
      return t2
    end,
}

function api.onBindPlayAudio(uri, entry, tunnel, param)
  local id = uri.."/"..entry
  LOGD(TAG, "onBindPlayAudio: " .. id)
  if PlayAudioInstanceTable[id] then 
    tunnel:detach()
    LOGD(TAG, "onBindPlayAudio: ", "already bind")
    return
  end
  local pa = sPlayAudio:new(uri, entry, tunnel)
  LOGD(TAG, "onBindPlayAudio over: pa = " .. tostring(pa))
  PlayAudioInstanceTable[id] = pa
end

function api:actionPlayAudio(f) 
  callback = f
end

return api
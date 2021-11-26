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
      if not info.newsocket then return nil end
      if not info.uri then return nil end
      if not info.encoding.type then return nil end
      if not info.encoding.codec.rate then return nil end
      if not info.encoding.codec.channel then return nil end
      if not info.encoding.codec.format then return nil end

      if info.newsocket == "true" then
        -- create pairs socket
        local t1, t2, b = FD:socketpair()
        if not b then return nil end
        if callback then callback(info, t1) end
        -- return socket
        LOGD(TAG, "return socket to client")
        return t2
      elseif info.uri ~= "" then
        if callback then callback(info) end
      end
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
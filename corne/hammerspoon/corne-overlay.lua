-- Corne: shows Corne Dojo (overlay mode) while ⌘Esc is held. "Fijar" in the window, or the KB-01
-- menu bar item, keeps it open; "Mini" pins a small translucent thumbnail (draggable, bottom-right by default).
-- The layer tabs in the window switch the layer shown. It reopens in the last size used (Mini or Grande).
local M = {}

local dir = hs.configdir .. "/corne/"
local PAGE = "file://" .. dir .. "corne-dojo.html#overlay"
local MINI_ALPHA = 0.8

local view, pinned, pageH
local mini = hs.settings.get("corne.mini") == true
local miniPos = hs.settings.get("corne.miniPos") -- {x, y} after dragging the thumbnail

local function setMini(m)
  mini = m
  hs.settings.set("corne.mini", m)
end

-- Window sized to the board. Full: the page uses --u = (width - 96px - 350px) / 13.7, capped at 84px
-- (350px is the 3D layer stack column).
-- Mini: --u = (width - 44px) / 13.7, at most 40% of the screen width (well under 1/4 of the screen).
local function frame()
  local s = hs.screen.mainScreen():frame()
  if mini then
    local w = math.min(s.w * 0.4, 560)
    local u = (w - 44) / 13.7
    local h = u * 5.15 + 76  -- board + tab bar + hazard stripe
    if miniPos then return { x = miniPos.x, y = miniPos.y, w = w, h = h } end
    return { x = s.x + s.w - w - 16, y = s.y + s.h - h - 16, w = w, h = h }
  end
  local w = math.min(s.w * 0.9, 84 * 13.7 + 96 + 350)
  local u = math.min(84, (w - 96 - 350) / 13.7)
  local h = math.min(s.h * 0.9, pageH or (u * 5.15 + 190))
  return { x = s.x + (s.w - w) / 2, y = s.y + (s.h - h) / 2, w = w, h = h }
end

local function sync()
  if not view then return end
  view:evaluateJavaScript(("window.setPinned && setPinned(%s); window.setMini && setMini(%s)")
    :format(tostring(pinned == true), tostring(mini == true)))
  view:frame(frame()):alpha(mini and MINI_ALPHA or 1)
end

local function hide()
  if view then view:hide() end
end

local function show()
  if not view then
    view = hs.webview.new(frame(), {}, M.controller)
      :windowStyle({ "borderless" })
      :level(hs.drawing.windowLevels.overlay)
      :behavior(hs.drawing.windowBehaviors.canJoinAllSpaces)
      :allowTextEntry(true)
      :transparent(false)
      :shadow(true)
      :url(PAGE)
  end
  view:show()
  sync()
end

function M.toggle()
  pinned = not pinned
  if pinned then
    show()
    view:bringToFront(true)
  else
    hide()
  end
  sync()
end

function M.toggleMini()
  setMini(not mini)
  pinned = true
  show()
end

M.controller = hs.webview.usercontent.new("corne")
M.controller:setCallback(function(msg)
  local body = msg.body
  if body == "ready" then
    sync()
  elseif body:sub(1, 2) == "h:" then
    pageH = tonumber(body:sub(3))
    if view and not mini then view:frame(frame()) end
  elseif body:sub(1, 5) == "move:" then
    -- Dragging the thumbnail: the page sends the mouse movement in screen points.
    local dx, dy = body:match("move:(%-?[%d.]+),(%-?[%d.]+)")
    if view and mini and dx then
      local f = view:frame()
      f.x, f.y = f.x + tonumber(dx), f.y + tonumber(dy)
      view:frame(f)
      miniPos = { x = f.x, y = f.y }
    end
  elseif body == "moved" then
    hs.settings.set("corne.miniPos", miniPos)
  elseif body == "pin" then
    M.toggle()
  elseif body == "mini" then
    M.toggleMini()
  elseif body == "close" then
    pinned = false
    sync()
    hide()
  end
end)

-- Holding ⌘Esc shows the window in the last size used; if it is pinned it stays as is.
M.hotkey = hs.hotkey.bind({ "cmd" }, "escape", function()
  if not pinned then show() end
end, function()
  if not pinned then hide() end
end)

-- Reload the window when corne-dojo.html is copied over again.
M.watcher = hs.pathwatcher.new(dir, function(files)
  for _, f in ipairs(files) do
    if f:match("corne%-dojo%.html$") and view then view:reload() end
  end
end):start()

M.menu = hs.menubar.new()
-- Menu bar badge: "KB-01" in lilac on a white rounded plate (drawn with hs.canvas, not a template icon).
local badge = hs.canvas.new({ x = 0, y = 0, w = 52, h = 18 })
badge[1] = { type = "rectangle", action = "fill", fillColor = { white = 1 },
  roundedRectRadii = { xRadius = 4, yRadius = 4 }, frame = { x = 1, y = 1, w = 50, h = 16 } }
badge[2] = { type = "text", text = hs.styledtext.new("KB-01", {
  font = { name = ".AppleSystemUIFontBold", size = 11 }, color = { hex = "#7b45c4" },
  paragraphStyle = { alignment = "center" } }), frame = { x = 0, y = 2, w = 52, h = 16 } }
M.menu:setIcon(badge:imageFromCanvas(), false)
badge:delete()
M.menu:setTooltip("Corne: show/hide layers")
M.menu:setClickCallback(M.toggle)

-- hammerspoon://corne-toggle (the button in Corne Dojo)
hs.urlevent.bind("corne-toggle", M.toggle)

return M

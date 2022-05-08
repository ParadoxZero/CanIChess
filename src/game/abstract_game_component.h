#ifndef __GAME_ABSTRACT_GAME_COMPONENT_
#define __GAME_ABSTRACT_GAME_COMPONENT_

#include "../renderer/api/event.h"
class AbstractGameComponent {
public:
  virtual bool HandlePointerEvent(renderer::api::PointerEvent) = 0;
  virtual bool HandleKeyboardEvent(renderer::api::KeyboardEvent) = 0;
  virtual bool HandleSystemEvent(renderer::api::SystemEvent) = 0;

  virtual bool addSprite
};

#endif
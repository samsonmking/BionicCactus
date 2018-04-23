#ifndef MOCK_LIGHT_H
#define MOCK_LIGHT_H

#include "sensors/light/Light.hpp"

namespace Sensors {
  namespace Light {

    class MockLight : public Light {
    public:
      virtual void loop() {

      };
      bool on = false;
      virtual bool isOn() {
        return on;
      };
    };
    
  }
}

#endif

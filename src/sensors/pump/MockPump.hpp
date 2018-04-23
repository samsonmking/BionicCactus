#ifndef MOCK_PUMP_H
#define MOCK_PUMP_H

#include "Pump.hpp"

namespace Sensors {
  namespace Pump {

    class MockPump : public Pump {
    public:
      int lastVol = 0;
      virtual void setVolume(int vol) {
        lastVol = vol;
      }
      bool dispenseIsDone = false;
      virtual bool dispenseDone() {
        return dispenseIsDone;
      }
      virtual void loop() {

      };
      virtual void prime() {

      }
      virtual void empty() {

      }
    };
    
  }
}

#endif

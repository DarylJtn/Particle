#pragma once

/* U8glib library by some chinese company
 */

// This will load the definition for common Particle variable types
#include "Particle.h"

// This is your main class that users will import into their application
class U8glib
{
public:
  /**
   * Constructor
   */
  U8glib();

  /**
   * Example method
   */
  void begin();

  /**
   * Example method
   */
  void process();

private:
  /**
   * Example private method
   */
  void doit();
};

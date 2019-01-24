/* U8glib library by some chinese company
 */

#include "U8glib.h"

/**
 * Constructor.
 */
U8glib::U8glib()
{
  // be sure not to call anything that requires hardware be initialized here, put those in begin()
}

/**
 * Example method.
 */
void U8glib::begin()
{
    // initialize hardware
    Serial.println("called begin");
}

/**
 * Example method.
 */
void U8glib::process()
{
    // do something useful
    Serial.println("called process");
    doit();
}

/**
* Example private method
*/
void U8glib::doit()
{
    Serial.println("called doit");
}

#ifndef ANTARES_INCLUDE_LIB_CEREBELLUM_BOARD_H
#define ANTARES_INCLUDE_LIB_CEREBELLUM_BOARD_H

/**
 * Include specific board configuration file
 */

#if defined(CONFIG_CONTRIB_CEREBELLUM_BOARD_CEREMOTOR_F1)
        #include <lib/cerebellum/boards/ceremotor_v2.h>
#elif defined(CONFIG_CONTRIB_CEREBELLUM_BOARD_STEPPER_U4)
        #include <lib/cerebellum/boards/cerestepper_u4.h>
#endif

#endif

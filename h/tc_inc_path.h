/*====================================================================
* Project:  Board Support Package (BSP)
* Function: macros for handling different AURIX TC27x devices and boards
*
* Copyright HighTec EDV-Systeme GmbH 1982-2019
*====================================================================*/

#ifndef __TC_INC_PATH_H__
#define __TC_INC_PATH_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(__TC27XX__)
# if defined(TRIBOARD_TC275A) || defined(TRIBOARD_TC27XA) || defined(APPKIT_TC275TU) || defined(APPKIT_TC275TE)
#  define TCPATH		tc27xa
#  define RUN_ON_TC27XA	1
# elif defined(TRIBOARD_TC275B) || defined(TRIBOARD_TC27XB) || defined(APPKIT_TC275TU_B)
#  define TCPATH		tc27xb
#  define RUN_ON_TC27XA	0
# elif defined(TRIBOARD_TC275C) || defined(TRIBOARD_TC277C) || defined(TRIBOARD_TC27XC) || defined(APPKIT_TC275TU_C) || defined(APPKIT_TC277TFT) || defined(SHIELDBUDDY_TC275C)
#  define TCPATH		tc27xc
#  define RUN_ON_TC27XA	0
# elif defined(TRIBOARD_TC275D) || defined(TRIBOARD_TC277D) || defined(TRIBOARD_TC27XD) || defined(APPKIT_TC277TFT_D) || defined(SHIELDBUDDY_TC275D)
#  define TCPATH		tc27xd
#  define RUN_ON_TC27XA	0
# else
#  error "Unknown TC27x board"
# endif /* TRIBOARD_TC275A */
#else
# error "Unsupported AURIX device"
#endif /* __TC27XX__ */

#define TC_STR(s)		# s
#define TC_INCLUDE(f)	TC_STR(f)

/* check for application kits */
#if defined(APPKIT_TC275TU) || defined(APPKIT_TC275TE) || defined(APPKIT_TC275TU_B) || defined(APPKIT_TC275TU_C)
# define APPKIT_TC2X5	1
#else
# define APPKIT_TC2X5	0
#endif /* APPKIT_TC2X5 */
#if defined(APPKIT_TC277TFT) || defined(APPKIT_TC277TFT_D)
# define APPKIT_TC2X7	1
#else
# define APPKIT_TC2X7	0
#endif /* APPKIT_TC2X7 */
#if (APPKIT_TC2X7 == 1) || (APPKIT_TC2X5 == 1)
# define RUN_ON_APPKIT	1
#else
# define RUN_ON_APPKIT	0
#endif /* APPKIT_TC2XX */

/* check for ShieldBuddy boards */
#if defined(SHIELDBUDDY_TC275C) || defined(SHIELDBUDDY_TC275D)
# define ON_SHIELDBUDDY	1
#else
# define ON_SHIELDBUDDY	0
#endif /* SHIELDBUDDY_TC275C || SHIELDBUDDY_TC275D */

/* check for TriBoard-TC2x7 */
#if defined(TRIBOARD_TC277C) || defined(TRIBOARD_TC277D)
# define TRIBOARD_TC2X7	1
#else
# define TRIBOARD_TC2X7	0
#endif /* TRIBOARD_TC277C || TRIBOARD_TC277D */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TC_INC_PATH_H__ */

/**
 * @file Ecore_Cocoa.h
 *
 * @brief Ecore_Cocoa Wrapper Library to interact with the Cocoa
 * envirnement (Mac OS X) from the E environment
 *
 */
#ifndef __ECORE_COCOA_H__
#define __ECORE_COCOA_H__

/*
 * DO NOT USE THIS HEADER. IT IS WORK IN PROGRESS. IT IS NOT FINAL AND
 * THE API MAY CHANGE.
 */

#ifndef ECORE_COCOA_WIP_GNSIDNQI
# warning "You are using a work in progress API. This API is not stable"
# warning "and is subject to change. You use this at your own risk."
#endif

#include <Eina.h>

#ifdef EAPI
# undef EAPI
#endif

#ifdef __GNUC__
# if __GNUC__ >= 4
#  define EAPI __attribute__ ((visibility("default")))
# else
#  define EAPI
# endif
#else
# define EAPI
#endif

#include "Ecore_Cocoa_Cursor.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ECORE_COCOA_WINDOW_PREDEF
/**
 * @typedef Ecore_Cocoa_Window
 * Opaque handler to manipulate a Cocoa Window through Ecore
 */
typedef struct _Ecore_Cocoa_Window Ecore_Cocoa_Window;
#endif /* ! _ECORE_COCOA_WINDOW_PREDEF */

/**
 * @typedef Ecore_Cocoa_Screen
 * Opaque handler to manipulate a Cocoa Screen through Ecore
 */
typedef struct _Ecore_Cocoa_Screen Ecore_Cocoa_Screen;

/**
 * @typedef Ecore_Cocoa_Object
 * Opaque handler to refer to an objective-c object (aka id)
 */
typedef void Ecore_Cocoa_Object;

/**
 * @typedef Ecore_Cocoa_Event_Window_Resize_Request
 * Type of event thrown when a Cocoa window is resized
 */
typedef struct _Ecore_Cocoa_Event_Window_Resize_Request Ecore_Cocoa_Event_Window_Resize_Request;

/**
 * @typedef Ecore_Cocoa_Event_Window_Focused
 * Type of event thrown when a Cocoa window receives focus
 */
typedef struct _Ecore_Cocoa_Event_Window_Focused Ecore_Cocoa_Event_Window_Focused;

/**
 * @typedef Ecore_Cocoa_Event_Window_Unfocused
 * Type of event thrown when a Cocoa window loses the focus
 */
typedef struct _Ecore_Cocoa_Event_Window_Unfocused Ecore_Cocoa_Event_Window_Unfocused;

/**
 * @typedef Ecore_Cocoa_Event_Window_Destroy
 * Type of event thrown when a Cocoa window gets destoyed
 */
typedef struct _Ecore_Cocoa_Event_Window_Destroy Ecore_Cocoa_Event_Window_Destroy;

/** Event triggered when a Cocoa window receives focus */
EAPI extern int ECORE_COCOA_EVENT_WINDOW_FOCUSED;

/** Event triggered when a Cocoa window loses focus */
EAPI extern int ECORE_COCOA_EVENT_WINDOW_UNFOCUSED;

/** Event triggered when a Cocoa window is resized */
EAPI extern int ECORE_COCOA_EVENT_WINDOW_RESIZE_REQUEST;

/** Event triggered when a Cocoa window get destroyed */
EAPI extern int ECORE_COCOA_EVENT_WINDOW_DESTROY;

/**
 * @struct _Ecore_Cocoa_Event_Window_Resize_Request
 * Data available when a window is resized
 */
struct _Ecore_Cocoa_Event_Window_Resize_Request
{
   int             w; /**< Current width of the window */
   int             h; /**< Current height of the window */
   Ecore_Cocoa_Object *cocoa_window; /**< Handler of the Cocoa window */
};

struct _Ecore_Cocoa_Event_Window_Focused
{
   Ecore_Cocoa_Object *cocoa_window;
};

struct _Ecore_Cocoa_Event_Window_Unfocused
{
   Ecore_Cocoa_Object *cocoa_window;
};

struct _Ecore_Cocoa_Event_Window_Destroy
{
   Ecore_Cocoa_Object *cocoa_window;
};

/**
 * @typedef Ecore_Cocoa_Cnp_Type
 * Type used to interact with the Cocoa pasteboard.
 * It hold types that can apply to a context.
 */
typedef enum
{
   ECORE_COCOA_CNP_TYPE_UNKNOWN = 0, /**< Undefined type */
   ECORE_COCOA_CNP_TYPE_STRING  = (1 << 0), /**< String type (pure text) */
   ECORE_COCOA_CNP_TYPE_MARKUP  = (1 << 1), /**< Elementary markup */
   ECORE_COCOA_CNP_TYPE_IMAGE   = (1 << 2), /**< Image (all formats) */
   ECORE_COCOA_CNP_TYPE_HTML    = (1 << 3) /**< HTML */
} Ecore_Cocoa_Cnp_Type;


/*============================================================================*
 *                                    Core                                    *
 *============================================================================*/

/**
 * Inits the Ecore_Cocoa library
 * @return How many times Ecore_Cocoa has been initted
 */
EAPI int ecore_cocoa_init(void);

/**
 * Shuts the Ecore_Cocoa library down
 * @return How many times Ecore_Cocoa has been initted
 */
EAPI int ecore_cocoa_shutdown(void);


/*============================================================================*
 *                                   Screen                                   *
 *============================================================================*/

/**
 * Retrieves the size of a Cocoa screen
 * @param screen The screen which size must be retrieved
 * @param [out] w The width of the screen
 * @param [out] h The height of the screen
 */
EAPI void ecore_cocoa_screen_size_get(Ecore_Cocoa_Screen *screen, int *w, int *h);


/*============================================================================*
 *                                   Window                                   *
 *============================================================================*/

/**
 * Creates a Cocoa window
 * @param x The origin (X) where the window must be created
 * @param y The origin (Y) where the window must be created
 * @param w The width of the window
 * @param h The height of the window
 * @return A handler on the window. NULL on failure
 */
EAPI Ecore_Cocoa_Window *ecore_cocoa_window_new(int x,
                                                int y,
                                                int w,
                                                int h);

/**
 * Releases a Cocoa window
 * @param window The window to be released
 */
EAPI void ecore_cocoa_window_free(Ecore_Cocoa_Window *window);

/**
 * Moves a Cocoa window to a given point
 * @param window The window to be moved
 * @param x The new origin of the window (X)
 * @param y The new origin of the window (Y)
 */
EAPI void ecore_cocoa_window_move(Ecore_Cocoa_Window *window,
                                  int                 x,
                                  int                 y);

/**
 * Resizes a Cocoa window to a given size
 * @param window The window to be moved
 * @param w The new width of the window
 * @param h The new height of the window
 */
EAPI void ecore_cocoa_window_resize(Ecore_Cocoa_Window *window,
                                    int                 w,
                                    int                 h);

/**
 * Moves and resizes a Cocoa window to a given point and size
 * @param window The window to be moved
 * @param x The new origin of the window (X)
 * @param y The new origin of the window (Y)
 * @param w The new width of the window
 * @param h The new height of the window
 * @see ecore_cocoa_window_resize()
 * @see ecore_cocoa_window_move()
 */
EAPI void ecore_cocoa_window_move_resize(Ecore_Cocoa_Window *window,
                                         int                 x,
                                         int                 y,
                                         int                 w,
                                         int                 h);

EAPI void ecore_cocoa_window_geometry_get(const Ecore_Cocoa_Window *window,
                                          int                      *x,
                                          int                      *y,
                                          int                      *w,
                                          int                      *h);

EAPI void ecore_cocoa_window_size_get(const Ecore_Cocoa_Window *window,
                                      int                      *w,
                                      int                      *h);

EAPI void ecore_cocoa_window_size_min_set(Ecore_Cocoa_Window *window,
                                          int                 w,
                                          int                 h);

EAPI void ecore_cocoa_window_size_min_get(const Ecore_Cocoa_Window *window,
                                          int                      *w,
                                          int                      *h);

EAPI void ecore_cocoa_window_size_max_set(Ecore_Cocoa_Window *window,
                                          int                 w,
                                          int                 h);

EAPI void ecore_cocoa_window_size_max_get(const Ecore_Cocoa_Window *window,
                                          int                      *w,
                                          int                      *h);

EAPI void ecore_cocoa_window_size_step_set(Ecore_Cocoa_Window *window,
                                           int                 w,
                                           int                 h);

EAPI void ecore_cocoa_window_size_step_get(const Ecore_Cocoa_Window *window,
                                           int                      *w,
                                           int                      *h);

EAPI void ecore_cocoa_window_show(Ecore_Cocoa_Window *window);

EAPI void ecore_cocoa_window_hide(Ecore_Cocoa_Window *window);

EAPI void ecore_cocoa_window_raise(Ecore_Cocoa_Window *window);

EAPI void ecore_cocoa_window_lower(Ecore_Cocoa_Window *window);

EAPI void ecore_cocoa_window_activate(Ecore_Cocoa_Window *window);

EAPI void ecore_cocoa_window_title_set(Ecore_Cocoa_Window *window,
                                       const char         *title);

EAPI void ecore_cocoa_window_iconified_set(Ecore_Cocoa_Window *window,
                                           Eina_Bool           on);

EAPI void ecore_cocoa_window_borderless_set(Ecore_Cocoa_Window *window,
                                            Eina_Bool           on);

EAPI void ecore_cocoa_window_view_set(Ecore_Cocoa_Window *window,
                                      Ecore_Cocoa_Object *view);

EAPI int ecore_cocoa_titlebar_height_get(void);

EAPI Ecore_Cocoa_Object *ecore_cocoa_window_get(const Ecore_Cocoa_Window *window);


EAPI Eina_Bool ecore_cocoa_selection_clipboard_set(const void *data, int size, Ecore_Cocoa_Cnp_Type type);

EAPI void *ecore_cocoa_selection_clipboard_get(int *size, Ecore_Cocoa_Cnp_Type type,
                                               Ecore_Cocoa_Cnp_Type *retrieved_types);

EAPI void ecore_cocoa_selection_clipboard_clear(void);

EAPI void ecore_cocoa_window_cursor_set(Ecore_Cocoa_Window *win, Ecore_Cocoa_Cursor c);
EAPI void ecore_cocoa_window_cursor_show(Ecore_Cocoa_Window *win, Eina_Bool show);

#ifdef __cplusplus
}
#endif

#undef EAPI
#define EAPI

#endif

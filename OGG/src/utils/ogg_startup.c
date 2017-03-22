#include <GL/glut.h>
#define OGG_GRAPHIC_STARTUP__INST____
#include "utils/ogg_startup.h"

# ifndef OGG_CUSTOM_STARTUP
# include <gl/freeglut.h>

def_startup(ogg_window)(
);

def_component(ogg_window) (
);

handler(ogg_window, OGG_PAINT_EVENT);

def_vtable(ogg_window) (
    [OGG_PAINT_EVENT] = ogg_handler(ogg_window, OGG_PAINT_EVENT)
);

static def_constructor(ogg_window, args)
{   /* do nothing */
}

static def_destructor(ogg_window)
{   /* do nothing */
}

def_handler(ogg_window, OGG_PAINT_EVENT)
{
    glFlush();
}

static ogg_window* main_window;

const ogg_com_ptr ogg_main_window(void)
{
    return main_window;
}

ogg_component_info ogg_fill_window(void)
{
    return ogg_default_info_ogg_component___(main_window);
}

static const glut_register glut_event_register[OGG_EVENT_COUNT] = {
    0,
    (glut_register)glutDisplayFunc,
    (glut_register)glutKeyboardFunc,
    (glut_register)glutSpecialFunc,
    (glut_register)glutMouseFunc,
    (glut_register)glutMotionFunc,
    (glut_register)glutPassiveMotionFunc,
    (glut_register)glutEntryFunc,
};

# include "events/ogg_default_handlers.h"
static glut_callback glut_events[OGG_EVENT_COUNT] = {
    0,
    ogg_default_handler(OGG_PAINT_EVENT),
    ogg_default_handler(OGG_KEYBOARD_EVENT),
    ogg_default_handler(OGG_SPECIAL_KEY_EVENT),
    ogg_default_handler(OGG_MOUSE_EVENT),
    ogg_default_handler(OGG_MOUSE_DRAG_EVENT),
    ogg_default_handler(OGG_MOUSE_MOVE_EVENT),
    ogg_default_handler(OGG_MOUSE_ENTRY_EVENT),
};

# ifdef ogg_default_handler
#  undef ogg_default_handler
# endif

void ogg_register_event(event event_name, glut_callback callback)
{
    glut_events[event_name] = callback;
}

int main(int argc, char *argv[])
{
    ogg_create(ogg_window)(
        .ogg_component = {
            .anchor = {
                .type = ogg_anchor_pec,
                .pec = {
                    .top_left = { 0, 0 },
                    .bottom_right = { 100, 100 }
                }
            },
            .parent = 0
        }
    )(main_window);

    ogg_startup_info st = {
        .argc = argc,
        .argv = argv,
        .display_mode = GLUT_RGB | GLUT_SINGLE,
        .window.position = { 100, 100 },
        .window.size = { 400, 400 },
        .window.title = "OGG Form"
    };

    ogg_main(&st);

    glutInit(&st.argc, st.argv);
    glutInitDisplayMode(st.display_mode);
    glutInitWindowPosition(st.window.position.x, st.window.position.y);
    glutInitWindowSize(st.window.size.width, st.window.size.height);
    glutCreateWindow(st.window.title);

    ogg_delegate();
    event i = 1;
    for (; i != OGG_EVENT_COUNT; ++i) {
        if (glut_events[i] != 0) {
            glut_event_register[i](glut_events[i]);
        }
    }
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutMainLoop();

    ogg_destroy(main_window);
    return ogg_exit_status();
}

# endif
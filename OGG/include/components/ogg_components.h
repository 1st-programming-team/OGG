#ifndef OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____
#define OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____
//#include "geometry.h"
#include "utils/ogg_utils.h"
#include "events/ogg_events.h"

# ifndef REG__GEOMETRY_SYSTEM__FLOAT__F___
#  define REG__GEOMETRY_SYSTEM__FLOAT__F___
    register_geometry_system(float, f);
# endif
# ifndef REG__GEOMETRY_SYSTEM__INT__I___
#  define REG__GEOMETRY_SYSTEM__INT__I___
    register_geometry_system(int, i)
# endif

    typedef coordi ogg_coord;
    typedef rectf ogg_pec_anchor;
    typedef recti ogg_coord_anchor;

    typedef enum {
        ogg_anchor_pec,
        ogg_anchor_coord
    } ogg_anchor_type;

    typedef struct {
        ogg_anchor_type type;
        union {
            ogg_pec_anchor pec;
            ogg_coord_anchor coord;
        };
    } ogg_anchor;

    static const ogg_anchor ogg_full_anchor = {
        .type = ogg_anchor_pec,
        .pec = {
            .top = 0,
            .bottom = 100,
            .left = 0,
            .right = 100
        }
    };

    typedef void *ogg_com_ptr;

    struct ogg_component_ty;

    struct ogg_subcomponent_ty;
    typedef struct ogg_subcomponent_ty {
        struct ogg_component_ty* object;
        struct ogg_subcomponent_ty* next;
    } ogg_subcomponent;

    typedef void (*ogg_event_handler)();
    typedef struct ogg_component_ty {
        ogg_event_handler* vptr;
        struct ogg_component_ty* parent;
        ogg_subcomponent* sub, * subrear;
        ogg_anchor_type anchor_type;
        union {
            ogg_pec_anchor pec;
            ogg_coord_anchor coord;
        };
    } ogg_component;

    typedef struct {
        ogg_component* parent;
        ogg_anchor anchor;
    } ogg_component_info;

    static const void (*parent_static_constructor_ogg_component__)() = 0;

    typedef unsigned ogg_handle_flag;
#  define OGG_HANDLED     (1)
#  define OGG_UNHANDLED   (0)

    /* get the absolute coord of a coord in canvas */
    coordf get_real_coord(ogg_com_ptr com_ptr, coordf pix);

    /* get the absolute anchor of a component in canvas */
    void get_component_real_anchor(ogg_com_ptr com_ptr, ogg_anchor* anchor);

    /* set the anchor of a component */
    void set_component_anchor(ogg_com_ptr com_ptr, const ogg_anchor* anchor);

    /* event handler */
    /* send event to a component with given args ... */
    void ogg_send_event(ogg_com_ptr com_ptr, event event_name, ...);

    /* destroy any component */
    void ogg_destroy(ogg_com_ptr com_ptr);

    /* create full anchor startup in a parent component */
    ogg_component_info ogg_default_info_ogg_component___(ogg_com_ptr parent);

    /* make a int-int coord */
    ogg_coord coord(int x, int y);

#  define OGG_EXPAND_ARGS_DBL_BRAK(...)                                 \
        __VA_ARGS__                                                     \
    })

#  define OGG_EXPAND_ARGS_WITH_BRAK(...)                                \
        __VA_ARGS__                                                     \
    }

#  define def_startup_inh(T, super_class)                               \
    struct OGG_COMPONENT_STARTUP_##T##_info;                            \
    typedef struct OGG_COMPONENT_STARTUP_##T##_info T##_info;           \
    T##_info ogg_default_info_##T##___(ogg_com_ptr);                    \
    extern super_class##_info ogg_default_info_##super_class##___(      \
        ogg_com_ptr);                                                   \
    static super_class##_info (*const parent_default_info_##T##__)(     \
            ogg_com_ptr) = ogg_default_info_##super_class##___;         \
    struct OGG_COMPONENT_STARTUP_##T##_info {                           \
        super_class##_info super_class;                                 \
        OGG_EXPAND_ARGS_WITH_BRAK

#  define OGG_DEFAULT_ARGS_EXPAND_ARGS(...)                             \
            __VA_ARGS__                                                 \
        };                                                              \
        return info;                                                    \
    }

#  define default_startup_inh(T, super_class)                           \
    T##_info ogg_default_info_##T##___(ogg_com_ptr parent)              \
    {                                                                   \
        T##_info info = {                                               \
            .super_class = parent_default_info_##T##__(parent),         \
            OGG_DEFAULT_ARGS_EXPAND_ARGS

#  define def_startup(component_type)                                   \
    def_startup_inh(component_type, ogg_component)

#  define default_startup(component_type)                               \
    default_startup_inh(component_type, ogg_component)

#  define ogg_default(T)                                                \
    ogg_default_info_##T##___


#  define def_component_inh(T, super_class)                             \
    struct OGG_COMPONENT_HELPER_##T;                                    \
    typedef struct OGG_COMPONENT_HELPER_##T T;                          \
    void ogg_static_constructor_##T##___(T*, const void*);              \
    extern void ogg_static_constructor_##super_class##___(              \
        super_class*, const void*);                                     \
    static void (*const parent_static_constructor_##T##__)(             \
            super_class*, const void*) =                                \
        ogg_static_constructor_##super_class##___;                      \
    struct OGG_COMPONENT_HELPER_##T {                                   \
        super_class super;                                              \
        OGG_EXPAND_ARGS_WITH_BRAK

#  define def_component(component_type)                                 \
    def_component_inh(component_type, ogg_component)

#  define def_vtable(component_type)                                    \
    static ogg_event_handler component_type##_vtable[OGG_EVENT_COUNT]= {\
        OGG_EXPAND_ARGS_WITH_BRAK


#  define ogg_startup(T)                                                \
    T##_info

#  define OGG_CREATOR_RAW__HELPER_DEF(st)                               \
        object__constructor__(&st);                                     \
    } while (0)

#  define ogg_create_def_raw(T)                                         \
	do {                                                                \
        static T* (*object__constructor__)() =                          \
            ogg_constructor_##T##___;                                   \
        OGG_CREATOR_RAW__HELPER_DEF

#  define OGG_CREATOR_RAW__FINISH(object)                               \
        object = object__constructor__(object__startup_info__);         \
    } while (0)

#  define OGG_CREATOR_RAW__HELPER(st)                                   \
        const ogg_startup(T)* object__startup_info__ = &st;             \
        OGG_CREATOR_RAW__FINISH

#  define ogg_create_raw(T)                                             \
	do {                                                                \
        static T* (*object__constructor__)() =                          \
            ogg_constructor_##T##___;                                   \
        OGG_CREATOR_RAW__HELPER


#  define OGG_CREATOR__HELPER_DEF(...)                                  \
            __VA_ARGS__                                                 \
        };                                                              \
        object__constructor__(&object__startup_info__);                 \
    } while (0)

#  define ogg_create_def(T)                                             \
	do {                                                                \
        static T* (*object__constructor__)() =                          \
            ogg_constructor_##T##___;                                   \
        const ogg_startup(T) object__startup_info__ = {                 \
            OGG_CREATOR__HELPER_DEF

#  define OGG_CREATOR__FINISH(object)                                   \
        object = object__constructor__(&object__startup_info__);        \
    } while (0)

#  define OGG_CREATOR__HELPER(...)                                      \
            __VA_ARGS__                                                 \
        };                                                              \
        OGG_CREATOR__FINISH

#  define ogg_create(T)                                                 \
	do {                                                                \
        static T* (*object__constructor__)() =                          \
            ogg_constructor_##T##___;                                   \
        const ogg_startup(T) object__startup_info__ = {                 \
            OGG_CREATOR__HELPER


#  define constructor(T)                                                \
    T* ogg_constructor_##T##___(const T##_info* args)

#  ifdef DEBUG
#    define def_constructor(T, args_name)                               \
    T* ogg_constructor_##T##___(const T##_info* args_name)              \
    {                                                                   \
        T* object = (T*)malloc(sizeof(T));                              \
        alloc_memory++;                                                 \
        void ogg_static_constructor_##T##___(T*, const void*);          \
        ogg_static_constructor_##T##___(object, args_name);             \
        ((ogg_component*)object)->vptr = T##_vtable;                    \
        return object;                                                  \
    }                                                                   \
    void ogg_static_constructor_##T##___(T* object, const void* args)   \
    {                                                                   \
        void create_##T(T* this, const T##_info* args_name);            \
        if (parent_static_constructor_##T##__ != 0)                     \
            parent_static_constructor_##T##__((void*)object, args);     \
        create_##T(object, (const T##_info*)args);                      \
    }                                                                   \
    void create_##T(T* this, const T##_info* args_name)
#  else
#    define def_constructor(T, args_name)                               \
    T* ogg_constructor_##T##___(const T##_info* args_name)              \
    {                                                                   \
        T* object = (T*)malloc(sizeof(T));                              \
        void ogg_static_constructor_##T##___(T*, const void*);          \
        ogg_static_constructor_##T##___(object, args_name);             \
        ((ogg_component*)object)->vptr = T##_vtable;                    \
        return object;                                                  \
    }                                                                   \
    void ogg_static_constructor_##T##___(T* object, const void* args)   \
    {                                                                   \
        void create_##T(T* this, const T##_info* args_name);            \
        if (parent_static_constructor_##T##__ != 0)                     \
            parent_static_constructor_##T##__((void*)object, args);     \
        create_##T(object, (const T##_info*)args);                      \
    }                                                                   \
    void create_##T(T* this, const T##_info* args_name)
#  endif

#endif //OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____
#include "efl_animation_private.h"

static void
_target_del_cb(void *data, const Efl_Event *event EINA_UNUSED)
{
   Eo *eo_obj = data;

   EFL_ANIMATION_CHECK_OR_RETURN(eo_obj);
   EFL_ANIMATION_DATA_GET(eo_obj, pd);

   pd->target = NULL;
}

EOLIAN static void
_efl_animation_target_set(Eo *eo_obj,
                          Efl_Animation_Data *pd,
                          Efl_Canvas_Object *target)
{
   EFL_ANIMATION_CHECK_OR_RETURN(eo_obj);

   efl_event_callback_add(target, EFL_EVENT_DEL, _target_del_cb, eo_obj);

   pd->target = target;
}

EOLIAN static Efl_Canvas_Object *
_efl_animation_target_get(Eo *eo_obj, Efl_Animation_Data *pd)
{
   EFL_ANIMATION_CHECK_OR_RETURN(eo_obj, NULL);

   return pd->target;
}

EOLIAN static void
_efl_animation_duration_set(Eo *eo_obj,
                            Efl_Animation_Data *pd,
                            double duration)
{
   EFL_ANIMATION_CHECK_OR_RETURN(eo_obj);

   pd->duration = duration;
}

EOLIAN static double
_efl_animation_duration_get(Eo *eo_obj, Efl_Animation_Data *pd)
{
   EFL_ANIMATION_CHECK_OR_RETURN(eo_obj, 0.0);

   return pd->duration;
}

EOLIAN static Eina_Bool
_efl_animation_is_deleted(Eo *eo_obj, Efl_Animation_Data *pd)
{
   EINA_SAFETY_ON_NULL_RETURN_VAL(eo_obj, EINA_TRUE);

   return pd->is_deleted;
}

EOLIAN static void
_efl_animation_final_state_keep_set(Eo *eo_obj,
                                    Efl_Animation_Data *pd,
                                    Eina_Bool keep_final_state)
{
   EFL_ANIMATION_CHECK_OR_RETURN(eo_obj);

   if (pd->keep_final_state == keep_final_state) return;

   pd->keep_final_state = !!keep_final_state;
}

EOLIAN static Eina_Bool
_efl_animation_final_state_keep_get(Eo *eo_obj, Efl_Animation_Data *pd)
{
   EFL_ANIMATION_CHECK_OR_RETURN(eo_obj, EINA_FALSE);

   return pd->keep_final_state;
}

EOLIAN static Efl_Animation_Object *
_efl_animation_object_create(Eo *eo_obj, Efl_Animation_Data *pd EINA_UNUSED)
{
   EFL_ANIMATION_CHECK_OR_RETURN(eo_obj, NULL);

   Efl_Animation_Object *anim_obj
      = efl_add(EFL_ANIMATION_OBJECT_CLASS, NULL);

   Efl_Canvas_Object *target = efl_animation_target_get(eo_obj);
   efl_animation_object_target_set(anim_obj, target);

   Eina_Bool state_keep = efl_animation_final_state_keep_get(eo_obj);
   efl_animation_object_final_state_keep_set(anim_obj, state_keep);

   double duration = efl_animation_duration_get(eo_obj);
   efl_animation_object_duration_set(anim_obj, duration);

   return anim_obj;
}

EOLIAN static Efl_Object *
_efl_animation_efl_object_constructor(Eo *eo_obj,
                                      Efl_Animation_Data *pd)
{
   eo_obj = efl_constructor(efl_super(eo_obj, MY_CLASS));

   pd->target = NULL;

   pd->duration = 0.0;

   pd->is_deleted = EINA_FALSE;
   pd->keep_final_state = EINA_FALSE;

   return eo_obj;
}

EOLIAN static void
_efl_animation_efl_object_destructor(Eo *eo_obj, Efl_Animation_Data *pd)
{
   pd->is_deleted = EINA_TRUE;

   if (pd->target)
     efl_event_callback_del(pd->target, EFL_EVENT_DEL, _target_del_cb, eo_obj);

   efl_destructor(efl_super(eo_obj, MY_CLASS));
}

#include "efl_animation.eo.c"
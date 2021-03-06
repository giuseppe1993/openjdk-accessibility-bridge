#include <stdio.h>
#include "mappingEnumerators.h"

AtkRole mapping_role_from_Java(const char * role)
{
    if ( strcmp(role,"frame") == 0 )
      return ATK_ROLE_FRAME;
    if ( strcmp(role,"root pane") == 0 )
      return ATK_ROLE_ROOT_PANE;
    if ( strcmp(role,"layered pane") == 0 )
      return ATK_ROLE_LAYERED_PANE;
    if ( strcmp(role,"panel") == 0 )
      return ATK_ROLE_PANEL;
    if ( strcmp(role,"menu bar") == 0 )
      return ATK_ROLE_MENU_BAR;
    if ( strcmp(role,"menu") == 0 )
      return ATK_ROLE_MENU;
    if ( strcmp(role,"menu item") == 0 )
      return ATK_ROLE_MENU_ITEM;
    if ( strcmp(role,"check box") == 0 )
      return ATK_ROLE_CHECK_BOX;
    if ( strcmp(role,"separator") == 0 )
      return ATK_ROLE_SEPARATOR;
    if ( strcmp(role,"page tab list") == 0 )
      return ATK_ROLE_PAGE_TAB_LIST;
    if ( strcmp(role,"page tab") == 0 )
      return ATK_ROLE_PAGE_TAB;
    if ( strcmp(role,"window") == 0 )
        return ATK_ROLE_WINDOW;
    if ( strcmp(role,"popup menu")  == 0 )
        return ATK_ROLE_POPUP_MENU;
    g_return_val_if_reached(ATK_ROLE_INVALID);
}

AtkState mapping_state_from_Java(const char *state)
{
    if ( strcmp(state,"enabled") == 0 )
        return ATK_STATE_ENABLED;
    if ( strcmp(state,"focusable") == 0 )
        return ATK_STATE_FOCUSABLE;
    if ( strcmp(state,"visible") == 0 )
        return ATK_STATE_VISIBLE;
    if ( strcmp(state,"showing") == 0 )
        return ATK_STATE_SHOWING;
    if ( strcmp(state,"resizable") == 0 )
        return ATK_STATE_RESIZABLE;
    if ( strcmp(state,"opaque") == 0 )
        return ATK_STATE_OPAQUE;
    if ( strcmp(state,"selectable") == 0 )
        return ATK_STATE_SELECTABLE;
    if ( strcmp(state,"checked") == 0 )
        return ATK_STATE_CHECKED;
    if ( strcmp(state,"selected") == 0)
        return ATK_STATE_SELECTED;
    g_return_val_if_reached(ATK_STATE_INVALID);
}

AtkLayer mapping_layer_from_Java_role (const char * role)
{
    if ( strcmp(role,"some other role")  == 0 )
        return ATK_LAYER_BACKGROUND;
    if ( strcmp(role,"canvas")  == 0 )
        return ATK_LAYER_CANVAS;
    if ( ( strcmp(role,"panel") == 0 ) ||
        ( strcmp(role,"check box") == 0 ) ||
        ( strcmp(role,"menu bar") == 0 ) ||
        ( strcmp(role,"menu") == 0 ) ||
        ( strcmp(role,"menu item") == 0 ) ||
        ( strcmp(role,"check box") == 0 ) ||
        ( strcmp(role,"separator") == 0 ) ||
        ( strcmp(role,"page tab list") == 0 ) ||
        ( strcmp(role,"page tab") == 0 ) )
        return ATK_LAYER_WIDGET;
    if ( ( strcmp(role,"root pane") == 0 ) ||
        ( strcmp(role,"layered pane") == 0 ) )
        return ATK_LAYER_MDI;
    if ( ( strcmp(role,"window") == 0 ) ||
        ( strcmp(role,"popup menu")  == 0 ) )
        return ATK_LAYER_POPUP;
    if ( strcmp(role,"frame") == 0 )
        return ATK_LAYER_WINDOW;
    if ( strcmp(role,"unknown") == 0 )
        return ATK_LAYER_INVALID;
    g_return_val_if_reached(ATK_LAYER_INVALID);
}

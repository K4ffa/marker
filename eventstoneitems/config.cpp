class CfgPatches
{
    class eventstoneitems
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "DZ_Data"
        };
    };
};
class CfgVehicles
{
    class Inventory_Base;
    class Not_SmallStone_Base : Inventory_Base
    {
        scope=0;
        displayName="Nope";
        descriptionShort="Nope";
        model="\dz\gear\consumables\SmallStone.p3d";
        animClass="NoFireClass";
        weight=100;
        itemSize[]={1, 1};
        hiddenSelections[]={"zbytek"};
        hiddenSelectionsTextures[]=
        {"#(argb,8,8,3)color(0.00,0.00,0.00,0.00,co)"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints=1000;
                    healthLevels[]={{1, {""}}, {0.7, {""}}, {0.5, {""}}, {0.3, {""}}, {0, {""}}};
                };
            };
        };
    };
    class Ninjin_EventItemPolice : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItemConvoy : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItemTrain : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItemCustom : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem1 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem2 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem3 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem4 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem5 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem6 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem7 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem8 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem9 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem11 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem12 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem13 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem14 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem15 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem16 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem17 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem18 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem19 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
    class Ninjin_EventItem20 : Not_SmallStone_Base
    {
        scope=2;
        displayName="";
        descriptionShort="";
    };
};
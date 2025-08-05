#ifdef MuchCarKey
modded class ActionPickLockOnCar
{
    override void OnStartServer(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        if (!player || !player.GetIdentity())
        {
            NinjinsPvPPvE.LogWarning("[Error] Player or PlayerIdentity is null. Cannot process lockpicking.");
            return;
        }
        if (g_MainConfig && g_MainConfig.OnlyAllowLockPickInPvP == 1 && !player.netSync_IsInPvPZone && !player.ShouldBypassActionBlock())
        {
            NinjinsPvPPvE.LogDebug("[DEBUG] Lockpicking blocked: Player not in PvP zone.");
            ZoneManager.GetInstance().NotifyLockpickingDenied(player);
            player.GetActionManager().Interrupt();
            GetGame().ClearJunctureEx(player, action_data.m_MainItem);
            return;
        }
        string playerID   = player.GetIdentity().GetId();
        string playerName = player.GetIdentity().GetName();
        NinjinsPvPPvE.LogDebug("[DEBUG] Player started lockpicking: " + playerID + " (" + playerName + ")");
        vector carPosition;
        bool   carFound = false;
        Transport transport = Transport.Cast(action_data.m_Target.GetObject());
        if (!transport)
            transport = Transport.Cast(action_data.m_Target.GetParent());
        CarScript carScript = CarScript.Cast(transport);
        if (carScript)
        {
            carPosition = carScript.GetPosition();
            carFound    = true;
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[Error] CarScript is null. Cannot determine car position for lockpicking.");
        }
        if (g_MainConfig && g_MainConfig.EnableLockpickingZoneCreation && carFound)
        {
            string uniqueID = "DynamicPvPZone_Lockpick_" + playerID;
            if (ZoneManager.GetInstance().RemoveDynamicZone(uniqueID))
                NinjinsPvPPvE.LogDebug("[DEBUG] Replaced existing lock-picking zone: " + uniqueID);
            ZoneBase lockpickZone        = new ZoneBase();
            lockpickZone.name            = uniqueID;
            lockpickZone.type            = ZONE_TYPE_PVP;
            lockpickZone.shape           = ZoneShape.CIRCLE;
            lockpickZone.center          = carPosition;
            lockpickZone.radius          = g_MainConfig.LockpickingZoneRadius;
            lockpickZone.priority        = 10;
            lockpickZone.enableCustomMessages   = false;
            lockpickZone.customTitle            = "Lockpicking Zone";
            lockpickZone.customMessageEnter     = "You have entered a Lockpicking Zone";
            lockpickZone.customMessageExit      = "You have exited a Lockpicking Zone";
            lockpickZone.customIcon             = "Car";
            lockpickZone.notificationColor      = ARGB(255, 255, 0, 0);
            lockpickZone.dayConfigs = new array<ref DayConfig>();
            lockpickZone.dayConfigs.Insert(new DayConfig("Monday", 0, 24));
            lockpickZone.dayConfigs.Insert(new DayConfig("Tuesday", 0, 24));
            lockpickZone.dayConfigs.Insert(new DayConfig("Wednesday", 0, 24));
            lockpickZone.dayConfigs.Insert(new DayConfig("Thursday", 0, 24));
            lockpickZone.dayConfigs.Insert(new DayConfig("Friday", 0, 24));
            lockpickZone.dayConfigs.Insert(new DayConfig("Saturday", 0, 24));
            lockpickZone.dayConfigs.Insert(new DayConfig("Sunday", 0, 24));
            lockpickZone.zoneAlpha              = 150;
            lockpickZone.zoneRed                = 255;
            lockpickZone.zoneGreen              = 0;
            lockpickZone.zoneBlue               = 0;
            lockpickZone.forceFirstPerson       = true;
            lockpickZone.drawShape              = true;
            lockpickZone.UsesDisallowedVehicles = false;
            ZoneManager.GetInstance().RegisterDynamicZone(lockpickZone);
            if (g_MainConfig.LockPickZoneDeletionTime > 0)
            {
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.RemoveLockpickZoneDelayed,g_MainConfig.LockPickZoneDeletionTime * 1000,false,uniqueID);
            }
        }
        if (g_MainConfig && g_MainConfig.EnableLockpickingNotification && carFound)
        {
            string notificationTitle    = g_MainConfig.LockpickNotificationTitle;
            string notificationMessage  = playerName + g_MainConfig.LockpickNotificationMessage;
            string notificationIconPath = g_MainConfig.ResolveIcon(g_MainConfig.LockpickNotificationIconPath);
            int    notificationColor    = g_MainConfig.LockpickNotificationColor;
            float  notificationDuration = 5.0;
            ZoneManager.GetInstance().BroadcastNotification(notificationTitle,notificationMessage,notificationIconPath,notificationColor,notificationDuration,carPosition);
        }
        super.OnStartServer(action_data);
    }
    void RemoveLockpickZoneDelayed(string uniqueID)
    {
        if (ZoneManager.GetInstance().RemoveDynamicZone(uniqueID))
            NinjinsPvPPvE.LogDebug("[DEBUG] Lockpicking zone removed after countdown: " + uniqueID);
    }
}
#endif

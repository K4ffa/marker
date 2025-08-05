class CfgPatches
{
	class NinjinsPvPPvE
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[] = {"DZ_Characters", "DZ_Data"};
	};
};
class CfgMods
{
	class NinjinsPvPPvE
	{
		dir="NinjinsPvPPvE";
		picture="";
		action="";
		hideName=1;
		inputs = "NinjinsPvPPvE/data/inputs.xml";
		hidePicture=1;
		name="NinjinsPvPPvE";
		credits="Naij0";
		author="Naij0";
		authorID="0";
		version="4.03";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"NinjinsPvPPvE/scripts/Common",
					"NinjinsPvPPvE/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"NinjinsPvPPvE/scripts/Common",
					"NinjinsPvPPvE/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"NinjinsPvPPvE/scripts/Common",
					"NinjinsPvPPvE/scripts/5_Mission"
				};
			};
		};
	};
};
class CfgVehicles
{
};

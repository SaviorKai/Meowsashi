// All rights reserved © 2019 Ivan Carl Engelbrecht

using UnrealBuildTool;
using System.Collections.Generic;

public class MeowsashiTarget : TargetRules
{
	public MeowsashiTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Meowsashi" } );
	}
}

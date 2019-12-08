// All rights reserved © 2019 Ivan Carl Engelbrecht

using UnrealBuildTool;
using System.Collections.Generic;

public class MeowsashiEditorTarget : TargetRules
{
	public MeowsashiEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Meowsashi" } );
	}
}

// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class The_VisionEditorTarget : TargetRules
{
	public The_VisionEditorTarget(TargetInfo Target) : base (Target)
	{
		Type = TargetType.Editor;

        ExtraModuleNames.Add("The_Vision");
	}

	//
	// TargetRules interface.
	//

	//public override void SetupBinaries(
	//	TargetInfo Target,
	//	ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
	//	ref List<string> OutExtraModuleNames
	//	)
	//{
	//	OutExtraModuleNames.Add("The_Vision");
	//}
}

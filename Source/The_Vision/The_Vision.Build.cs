// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class The_Vision : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    public The_Vision(ReadOnlyTargetRules Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",  "UMG", "Slate", "SlateCore"});
	}

   public bool LoadWwise(ReadOnlyTargetRules Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            //string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            //string LibrariesPath = Path.Combine(ThirdPartyPath, "Wwise", "Libraries");

            /*
            test your path with:
            using System; // Console.WriteLine("");
            Console.WriteLine("... LibrariesPath -> " + LibrariesPath);
            */

            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Wwise." + PlatformString + ".lib"));
        }

        if (isLibrarySupported)
        {
            // Include path
            
        }

        return isLibrarySupported;
    }
}





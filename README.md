# xdiff_dotnet
dotnet wrapper around xdiff

Note that VisualStudio will not currently copy the built xdiff 
library files to the dotnet_xdiff_test directory.
You must copy those files over manually.  You need the .dll at minimum and it's 
good to include the .lib, .exp, and .pdb as well. These can be found at the root of the 
solution in the x64 folder.  Copy them to the root of the dotnet_xdiff_test project
so they can be found when the .net code is run.


 

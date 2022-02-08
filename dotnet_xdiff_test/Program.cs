
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;

public class Test
{

    //BSTR merge(const char* orig_contents, const char* file1_contents, const char* file2_contents,
    //const char* orig_filename, const char* file1_name, const char* file2_name,
    //__int32 level, __int32 style)


    //todo - I don't know if ANSI is safe, but we can easily modify the wrapper if needed
    [DllImport(
      "xdiff.dll",
      CharSet = CharSet.Ansi,
      CallingConvention = CallingConvention.StdCall)]
    [return: MarshalAs(UnmanagedType.BStr)]
    static extern string merge(
      string orig_file_contents,
      string file1_contents,
      string file2_contents,
      string orig_filename,
      string file1_filename,
      string file2_filename,
      int level,
      int style);


    /* merge simplification levels 
    #define XDL_MERGE_MINIMAL 0
    #define XDL_MERGE_EAGER 1
    #define XDL_MERGE_ZEALOUS 2
    #define XDL_MERGE_ZEALOUS_ALNUM 3
    */

    public const int XDL_MERGE_LEVEL_MINIMAL = 0;
    public const int XDL_MERGE_LEVEL_EAGER = 1;
    public const int XDL_MERGE_LEVEL_ZEALOUS = 2;
    public const int XDL_MERGE_LEVEL_ZEALOUS_ALNUM = 3;

    /* merge style levels
     * #define XDL_MERGE_DIFF2 0
     * #define XDL_MERGE_DIFF3 1
     */
    public const int XDL_MERGE_STYLE_DIFF2 = 0;
    public const int XDL_MERGE_STYLE_DIFF3 = 0;

    public static void Main()
{
    Process proc = Process.GetCurrentProcess();
    long currentMemoryUsage;
    int n = 0;
    for (int i = 0; i < 1000 * 1000; i++)
    {
        if (i % 10000 == 0)
        {
            proc.Refresh();
            currentMemoryUsage = proc.PrivateMemorySize64;
            Console.WriteLine($"Usage afer {i} iterations is {currentMemoryUsage}");
        }
        string str_o = "I\nlike\nlooking\nat\nthose\ntraffic\nlights\n";
        string str_a = "I\nlove\nlooking\nat\nthose\n" + i.ToString() + "\ntraffic\nlightsasdf\n";
        string str_b = "I\nhate\nlooking\nat\nthose\ntraffic\ncameras\n";

        string result = merge(str_b, str_o, str_a, "base", "a", "b", XDL_MERGE_LEVEL_EAGER, XDL_MERGE_STYLE_DIFF3);
        n += result.Length;

        if (i == 0)
        {
            Console.WriteLine(result);
            Console.WriteLine("Touch any key to continue.  This will merge 1,000,000 times to check for memory leakage");
            Console.ReadKey();
        }
    }
}
}

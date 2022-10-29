using System;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace EasyRegex
{
	internal class Program
	{
		static void Main(string[] args)
		{
			//Regex p=<pattern> (r=<repleacement>)

			ArgumentLoader(args);
		}

		public static void ArgumentLoader(string[] args)
		{
			if (args.Length < 0 || (from val in args where val=="--help"||val=="-h" select val).Count() > 0)
			{
#warning Need refer OurOpenSource.TextUnit.HelpViewer

				Environment.Exit(0);
			}

			int i;
			for(i=0;i<args.Length; i++)
			{
				switch (args[i])
				{
					case "--pattern":
					case "-p":
				}
			}
		}
	}
}

using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;

namespace EasyRegex
{
	public class ProgramArguments
	{
		/// <summary>
		/// Input Text.
		/// </summary>
		public string InputText { get; set; }

		/// <summary>
		/// Pattern.
		/// </summary>
		public string Pattern { get; set; }

		public static readonly string? NoReplacement = null;
		/// <summary>
		/// Replacement.
		/// </summary>
		/// <remarks></remarks>
		public string? Replacement { get; set; }

		public Encoding Encoding { get; set; }

		public RegexOptions RegexOptions { get; set; }
	}
}

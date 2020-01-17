using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;

namespace WebService
{
    /// <summary>
    ///
    /// </summary>
    public static class StringExtension
    {
        /// <summary>
        /// Determines whether [is null or whitespace].
        /// </summary>
        /// <param name="s">The s.</param>
        /// <returns>
        /// <c>true</c> if [is null or whitespace] [the specified s]; otherwise, <c>false</c>.
        /// </returns>
        public static bool IsNullOrWhitespace(this string s)
        {
            return string.IsNullOrWhiteSpace(s);
        }

        /// <summary>
        /// Determines whether [is null or whitespace].
        /// </summary>
        /// <param name="s">The s.</param>
        /// <returns>
        /// <c>true</c> if [is null or empty] [the specified s]; otherwise, <c>false</c>.
        /// </returns>
        public static bool IsNullOrEmpty(this string s)
        {
            return string.IsNullOrEmpty(s);
        }
        /// <summary>
        /// Splits the CSV.
        /// </summary>
        /// <param name="csvList">The CSV list.</param>
        /// <param name="nullOrWhitespaceInputReturnsNull">if set to <c>true</c> [null or whitespace input returns null].</param>
        /// <returns></returns>
        public static List<string> SplitCsv(this string csvList, bool nullOrWhitespaceInputReturnsNull = false)
        {
            if (string.IsNullOrWhiteSpace(csvList))
            {
                return nullOrWhitespaceInputReturnsNull ? null : new List<string>();
            }

            return csvList
                .TrimEnd(',')
                .Split(',')
                .AsEnumerable()
                .Select(s => s.Trim())
                .ToList();
        }


        /// <summary>
        /// Converts to.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="data">The data.</param>
        /// <returns></returns>
        public static T ConvertTo<T>(this string data)
        {
            try
            {
                if (string.IsNullOrWhiteSpace(data))
                {
                    return default;
                }

                return (T)Convert.ChangeType(data, typeof(T), CultureInfo.CurrentCulture);
            }
            catch (InvalidCastException)
            { return default; }
            catch (FormatException)
            { return default; }
            catch (OverflowException)
            { return default; }
            catch (ArgumentNullException)
            { return default; }

        }

        /// <summary>
        /// Converts to.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="data">The data.</param>
        /// <returns></returns>
        public static T ConvertTo<T>(this object data)
        {
            try
            {
                if (data == null)
                {
                    return default;
                }

                return (T)Convert.ChangeType(data, typeof(T), CultureInfo.CurrentCulture);
            }
            catch (InvalidCastException)
            { return default; }
            catch (FormatException)
            { return default; }
            catch (OverflowException)
            { return default; }
            catch (ArgumentNullException)
            { return default; }
        }


        /// <summary>
        /// Converts to.
        /// </summary>
        /// <param name="data">The data.</param>
        /// <param name="typeName">Name of the type.</param>
        /// <returns></returns>
        public static object ConvertTo(this object data, string typeName)
        {
            try
            {
                if (typeName.IsNullOrEmpty())
                {
                    return data;
                }

                if (data == null)
                {
                    return null;
                }

                Type tp = Type.GetType($"system.{typeName}", false, true);
                if (tp == null)
                {
                    tp = Type.GetType(typeName, false, true);
                }

                if (tp != null)
                {
                    return Convert.ChangeType(data, tp, CultureInfo.CurrentCulture);
                }

                return data;
            }
            catch (InvalidCastException)
            { return default; }
            catch (FormatException)
            { return default; }
            catch (OverflowException)
            { return default; }
            catch (ArgumentNullException)
            { return default; }
        }

    }


}

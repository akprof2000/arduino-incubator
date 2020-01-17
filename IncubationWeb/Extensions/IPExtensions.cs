using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Security.Claims;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Http.Features;
using Microsoft.Extensions.Primitives;

namespace WebService
{
    /// <summary>
    ///
    /// </summary>
    public static class IPExtensions
    {
        /// <summary>
        /// Gets the user identifier.
        /// </summary>
        /// <param name="user">The user.</param>
        /// <returns></returns>
        public static string UserID(this ClaimsPrincipal user)
        {
            return user?.Claims?.FirstOrDefault(i => i.Type == "UserId")?.Value;
        }

        /// <summary>
        /// Gets the request ip.
        /// </summary>
        /// <param name="Request"></param>
        /// <param name="tryUseXForwardHeader">if set to <c>true</c> [try use x forward header].</param>
        /// <returns></returns>
        /// <exception cref="Exception">Unable to determine caller's IP.</exception>
        public static string GetRequestIP(this HttpRequest Request, bool tryUseXForwardHeader = true)
        {
            string ip = null;


            if (tryUseXForwardHeader)
            {
                List<string> strs = getHeaderValueAs<string>(Request, "X-Forwarded-For").SplitCsv();
                var localIp = "127.0.0.1";
                if (strs.Count > 1 || (strs.Any() && !strs.Contains(localIp)))
                {
                    ip = string.Join(";", strs.Where(x => !x.Contains(localIp, StringComparison.OrdinalIgnoreCase)));
                }
            }


            if (ip.IsNullOrWhitespace() && Request?.HttpContext?.Connection?.RemoteIpAddress != null)
            {
                ip = Request.HttpContext.Connection.RemoteIpAddress.ToString();

            }

            if (ip.IsNullOrWhitespace())
            {

                string ipt = Request?.HttpContext.Features.Get<IHttpConnectionFeature>()?.RemoteIpAddress.ToString();
                if (!ipt.IsNullOrWhitespace() && (ip.IsNullOrWhitespace() || string.Compare(ip, ipt, true, CultureInfo.CurrentCulture) != 0))
                {
                    ip = ipt;
                }
            }

            if (ip.IsNullOrWhitespace())
            {
                string ipt = getHeaderValueAs<string>(Request, "REMOTE_ADDR");
                if (!ipt.IsNullOrWhitespace() && (ip.IsNullOrWhitespace() || string.Compare(ip, ipt, true, CultureInfo.CurrentCulture) != 0))
                {
                    ip = ipt;
                }

            }
            return ip;
        }


        /// <summary>
        /// Gets the header value as.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="Request"></param>
        /// <param name="headerName">Name of the header.</param>
        /// <returns></returns>
        private static T getHeaderValueAs<T>(HttpRequest Request, string headerName)
        {
            StringValues values;

            if (Request?.HttpContext?.Request?.Headers?.TryGetValue(headerName, out values) ?? false)
            {
                string rawValues = values.ToString();   // writes out as Csv when there are multiple.

                if (!rawValues.IsNullOrWhitespace())
                {
                    return (T)Convert.ChangeType(values.ToString(), typeof(T), CultureInfo.CurrentCulture);
                }
            }
            return default;
        }

        /// <summary>
        /// Sids the specified user.
        /// </summary>
        /// <param name="user">The user.</param>
        /// <returns></returns>
        public static string SID(this ClaimsPrincipal user)
        {
            return user?.Claims?.FirstOrDefault(i => i.Type == "SessionId")?.Value;
        }
    }


}

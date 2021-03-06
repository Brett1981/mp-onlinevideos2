﻿using System;
using System.Text.RegularExpressions;
using System.Threading;

namespace OnlineVideos.Hoster
{
    public class GorillaVid : MyHosterBase
    {
        public override string GetHosterUrl()
        {
            return "GorillaVid.in";
        }

        public override string GetVideoUrl(string url)
        {
            url = url.Replace(@"http://", @"https://");
            string page = WebCache.Instance.GetWebData(url);
            if (!string.IsNullOrEmpty(page))
            {
                string sWaitTime = Helpers.StringUtils.GetRegExData(@"Wait\s(?:<(?:.|\n)*?>)?(?<waittime>\d*?)(?:<(?:.|\n)*?>)?\sseconds", page);
                int iWaitTime = 5;
                if (!string.IsNullOrEmpty(sWaitTime))
                {
                    if (!int.TryParse(sWaitTime, out iWaitTime))
                        iWaitTime = 5;
                }

                Thread.Sleep(iWaitTime * 1001);

                page = GetFromPost(url, page, true);

                //file:\s*'(?<Title>[^"]*)',
                Match n = Regex.Match(page, @"file:\s*'(?<url>[^']*)'");
                if (n.Success && Helpers.UriUtils.IsValidUri(n.Groups["url"].Value)) return n.Groups["url"].Value;
                n = Regex.Match(page, @"file:\s*""(?<url>[^""]*)""");
                if (n.Success && Helpers.UriUtils.IsValidUri(n.Groups["url"].Value)) return n.Groups["url"].Value;
                n = Regex.Match(page, @"src:\s'(?<url>[^']*)'");
                if (n.Success && Helpers.UriUtils.IsValidUri(n.Groups["url"].Value)) return n.Groups["url"].Value;
            }
            return String.Empty;
        }
    }

    public class GorillaVidCom : GorillaVid
    {
        public override string GetHosterUrl()
        {
            return "GorillaVid.com";
        }

        public override string GetVideoUrl(string url)
        {
            url = WebCache.Instance.GetRedirectedUrl(url);
            return base.GetVideoUrl(url);
        }
    }

}

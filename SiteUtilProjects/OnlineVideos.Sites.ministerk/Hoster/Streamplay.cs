﻿using Jurassic;
using System.Text.RegularExpressions;

namespace OnlineVideos.Hoster
{
    public class Streamplay : HosterBase
    {
        public override string GetHosterUrl()
        {
            return "streamplay.to";
        }

        public override string GetVideoUrl(string url)
        {
            if(!url.Contains("embed-"))
            {
                url = url.Replace("play.to/", "play.to/embed-");
            }
            if (!url.EndsWith(".html"))
            {
                url += ".html";
            }

            string data = GetWebData<string>(url);
            Regex rgx = new Regex(@">eval(?<js>.*?)</script>", RegexOptions.Singleline);
            Match m = rgx.Match(data);
            if (m.Success)
            {
                ScriptEngine engine = new ScriptEngine();
                string js = m.Groups["js"].Value;
                engine.Execute("var player = " + js + ";");
                engine.Execute("function getPlayer() { return player; };");
                data = engine.CallGlobalFunction("getPlayer").ToString();
                rgx = new Regex(@"file:""(?<url>http[^""]*?.mp4)""");
                m = rgx.Match(data);
                if (m.Success)
                {
                    return m.Groups["url"].Value;
                }
            }
            return "";
        }
    }
}

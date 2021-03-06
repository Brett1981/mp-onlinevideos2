﻿using OnlineVideos.Sites.Interfaces.WebBrowserPlayerService;
using System;
using System.ServiceModel;

namespace OnlineVideos.Sites.WebBrowserPlayerService.ServiceImplementation
{
    /// <summary>
    /// Player service implementation - these are messages from the client (OV) to the server (BrowserHost)
    /// </summary>
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.PerSession, 
                    ConcurrencyMode = ConcurrencyMode.Multiple, 
                    UseSynchronizationContext = false)]
    public class WebBrowserPlayerService :  IWebBrowserPlayerService
    {
        /// <summary>
        /// Let server applications know we have a new action
        /// </summary>
        public static event Action<string> OnNewActionReceived;

        /// <summary>
        /// New action has been received from the client
        /// </summary>
        /// <param name="action"></param>
        public void OnNewAction(string action)
        {
            if (OnNewActionReceived != null) OnNewActionReceived.Invoke(action);
        }
    }
}

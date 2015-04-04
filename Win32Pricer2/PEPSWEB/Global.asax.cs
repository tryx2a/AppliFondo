using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Optimization;
using System.Web.Routing;
using System.Web.Security;
using System.Web.SessionState;

namespace PEPSWEB
{
    public class Global : HttpApplication
    {
        void Application_Start(object sender, EventArgs e)
        {

            String _path = String.Concat(System.Environment.GetEnvironmentVariable("PATH"), ";", System.AppDomain.CurrentDomain.RelativeSearchPath);
            System.Environment.SetEnvironmentVariable("PATH", _path, EnvironmentVariableTarget.Process);

            HttpContext.Current.Application["timeStepSub"] = 4;
            HttpContext.Current.Application["H"] = 70;
            HttpContext.Current.Application["TourMC"] = 5000;
            HttpContext.Current.Application["today"] = DateTime.Now.ToString("dd/MM/yyyy");
            
            // Code qui s’exécute au démarrage de l’application
            RouteConfig.RegisterRoutes(RouteTable.Routes);
            BundleConfig.RegisterBundles(BundleTable.Bundles);
        }
    }
}
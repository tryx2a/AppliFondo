using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(PEPSWEB.Startup))]
namespace PEPSWEB
{
    public partial class Startup {
        public void Configuration(IAppBuilder app) {
            ConfigureAuth(app);
        }
    }
}

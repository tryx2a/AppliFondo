using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace PEPSWEB
{
    public partial class Settings : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(dconsts.Text))
            {
                dconsts.Text = HttpContext.Current.Application["timeStepSub"].ToString();
            }
            if (string.IsNullOrWhiteSpace(H.Text))
            {
                H.Text = HttpContext.Current.Application["H"].ToString();
            }
            if (string.IsNullOrWhiteSpace(mc.Text))
            {
                mc.Text = HttpContext.Current.Application["TourMC"].ToString();
            }
        }

        protected void saveSettings(object sender, EventArgs e)
        {
            HttpContext.Current.Application["timeStepSub"] = dconsts.Text;
            HttpContext.Current.Application["H"] = H.Text;
            HttpContext.Current.Application["TourMC"] = mc.Text;
        }
    }
}
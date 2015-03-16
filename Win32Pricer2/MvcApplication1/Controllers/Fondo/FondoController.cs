using MvcApplication1.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Wrapper2;

namespace MvcApplication1.Controllers.Fondo
{
    public class FondoController : Controller
    {
        //
        // GET: /Fondo/

        public ActionResult Index()
        {

            return View(new Models.Fondo());
        }

        


        [AcceptVerbs(HttpVerbs.Post)]
        private ActionResult View(Models.Fondo fondo)
        {
            double prix;
            double ic;
            double pnl;

            WrapperClass2 wc = new WrapperClass2();
            
            wc.computePriceWrapper();

            prix = wc.getPriceWrapper();
            ic = wc.getICWrapper();

            wc.computePnLWrapper();

            pnl = wc.getPnLWrapper();

            ViewData["Prix"] = prix.ToString();
            ViewData["IC"] = ic.ToString();
            ViewData["PnL"] = pnl.ToString();

            return View();
        }

    }
}

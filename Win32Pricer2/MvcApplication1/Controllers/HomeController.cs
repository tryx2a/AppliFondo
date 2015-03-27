using MvcApplication1.Models;
using MvcApplication1.ServiceReference;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace MvcApplication1.Controllers
{
    public class HomeController : Controller
    {
        //
        // GET: /Home/

        public ActionResult Index()
        {
            Panier panier = new Panier();
            DateTime debut = new DateTime(2010, 1, 4);
            DateTime fin = new DateTime(2010, 1, 4);
            List<MvcApplication1.Models.Action> ListeAction = panier.getListAction(debut,fin);

            ViewData["Panier"] = "<table class=\"table\"><tr><th>ISIN</th><th>Nom</th><th>Devise</th><th>Prix Spot</th></tr>";

                    

                    foreach (MvcApplication1.Models.Action action in ListeAction)
                    {
                        ViewData["Panier"] += "<tr><td>"+  action.isin + "</td><td>" + action.nom + "</td><td>"+action.devise+"</td><td>" + action.prix + "</td></tr>";
                    } 
                    ViewData["Panier"] +="</table>";

            return View();
        }

        


    }
}

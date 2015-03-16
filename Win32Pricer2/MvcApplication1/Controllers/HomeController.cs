using MvcApplication1.Models;
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
            List<MvcApplication1.Models.Action> ListeAction = panier.getListAction();
            
            ViewData["Panier"] = "<table class=\"table\"><tr><th></th><th>ISIN</th><th>Nom</th><th>Prix</th></tr>";

                    foreach (MvcApplication1.Models.Action action in ListeAction)
                    {
                        ViewData["Panier"] += "<tr><td><input type=\"checkbox\" aria-label=\"...\" checked></td><td>" + action.isin + "</td><td>" + action.nom + "</td><td>" + action.prix + "</td></tr>";
                    } 
                    ViewData["Panier"] +="</table>";

            return View();
        }

        


    }
}

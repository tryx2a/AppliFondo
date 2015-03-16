<%@ Page Language="C#" Inherits="System.Web.Mvc.ViewPage<dynamic>" %>

<!DOCTYPE html>

<html>
    <head runat="server">
    <meta name="viewport" content="width=device-width" />
    <title>Index</title>
    <link href="../../Content/bootstrap.css" rel="stylesheet" />
    
</head>
<body class="col-lg-12">
    <div class="page-header">
        <h1 class="alert alert-info">FONDO GARANTITO 2015</h1>
        <div>
            <div class="panel panel-primary">
                <div class="panel-heading">Données relatives au produit</div>
                <div class="panel-body">
                    <div class="input-group">
                        <span class="input-group-addon" id="sizing-addon2">Valeur liquidative de référence</span>
                        <input type="text" class="form-control" placeholder="Username" aria-describedby="sizing-addon2">
                        </div>
                </div>
            </div>

            <div class="panel panel-primary" id="panel_panier">
                <div class="panel-heading" >
                    <h4 class="panel-title">
                        <a data-toggle="collapse" data-parent="#panel_panier" href="#panier">Panier d'actifs </a>
                    </h4>
                </div>
                <div id="panier" class="panel-collapse collapse out">
                    <%=ViewData["Panier"] %>
                </div>
                    
            </div>

            <form action="/Fondo" method="post">
                <input type="submit" value="Cliquer ici pour lancer les calculs" />
            </form>
        </div>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
    <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/js/bootstrap.min.js"></script>
</body>
</html>

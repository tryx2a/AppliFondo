<%@ Page Language="C#" Inherits="System.Web.Mvc.ViewPage<MvcApplication1.Models.Fondo>" %>

<!DOCTYPE html>

<html>
<head runat="server">
    <meta name="viewport" content="width=device-width" />
    <title>Index</title>
    <link href="../../Content/bootstrap.css" rel="stylesheet" />
</head>
<body class="col-lg-12">
     <%using (Html.BeginForm())
    {
    %>
    <div class="page-header">
        <h1 class="alert alert-info">FONDO GARANTITO 2015</h1>
    <div>
    
    <div class="panel panel-primary">
                <div class="panel-heading">Résultats après calculs</div>
                <div class="panel-body">
                    
                    <div class="col-lg-6 input-group">
                        <span class="input-group-addon" >Prix : <%=ViewData["Prix"]%></span>
                    </div>
                    
                    </br>

                    <div class="col-lg-6 input-group">
                        <span class="input-group-addon" >Intervalle de confiance : <%=ViewData["IC"]%></span>
                    </div>

                    </br>

                    <div class="col-lg-6 input-group">
                        <span class="input-group-addon" >Résultats de la couverture : <%=ViewData["Couverture"]%></span>
                    </div>

                </div>
     </div>

   <%
    } %>

</body>

</html>

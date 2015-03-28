<%@ Page Language="C#" Inherits="System.Web.Mvc.ViewPage<MvcApplication1.Models.Fondo>" %>

<!DOCTYPE html>
<script runat="server">
    protected void Chart1_Init(object sender, EventArgs e)
    {
        DataPoint dp= new DataPoint(0,0);
        DataPoint dp1 = new DataPoint(2, 1);
        DataPoint dp2 = new DataPoint(8, -4);
        Chart1.Series[0].Points.Add(dp);
        Chart1.Series[0].Points.Add(dp1);
        Chart1.Series[0].Points.Add(dp2);
        
    }
</script>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <meta name="viewport" content="width=device-width" />
    <title>Index</title>
    <link href="../../Content/bootstrap.css" rel="stylesheet" />
  
</head>
<body class="col-lg-12">
     <form id="form1" runat="server">
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
                <asp:Chart ID="Chart1" runat="server" Visible="true"  Width="988px" EnableViewState="True" OnInit="Chart1_Init">
                     <Series>
                         <asp:Series ChartType="Line" Name="Series1">
                             
                         </asp:Series>
                     </Series>
                     <ChartAreas>
                         <asp:ChartArea Name="ChartArea1">
                         </asp:ChartArea>
                     </ChartAreas>
                 </asp:Chart>
                

     </div>

   <%
    } %>

         </div>
         </div>
         
     </form>

</body>

</html>

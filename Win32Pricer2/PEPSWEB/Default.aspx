<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="PEPSWEB._Default" %>

<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35" Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <br><br>
    <asp:Button id="sim" Text="Simuler" ForeColor="White"  BorderStyle="Ridge" Font-Bold="true" Width="150" Height="40" runat="server" BackColor="Black" OnClick="sim_Click"/>
    <br><br>

    <div id="res">
        <div style="float:left; width:550px">
            <asp:Label ID="prt" runat="server" Text="Prix: "></asp:Label>
        </div>
        <div style="float: left; width:200px">    
            <asp:TextBox id="pr" rows="10" TextMode="multiline" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="ict" runat="server" Text="Portefeuille de Couverture: "></asp:Label>
        </div>
        <div style="float: left; width:300px">
            <asp:TextBox id="intc" rows="10" TextMode="multiline" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="couvt" runat="server" Text="Part Investie au taux sans risque: "></asp:Label>
        </div>
        <div style="float: left; width:300px">
            <asp:TextBox id="couv" rows="10" TextMode="multiline" runat="server" />
        </div>
        <br><br>

        <asp:Chart ID="mainChart" runat="server" Visible="true" Height="500px" Width="988px" EnableViewState="True">
            <Series>
                <asp:Series ChartType="Line" Legend="legend" LegendText="Prix du Fondo Garantito" Name="price"></asp:Series>
                <asp:Series ChartType="Line" Legend="legend" LegendText="Valeur du Portefeuille de Couverture" Name="portfolio"></asp:Series>
               
            </Series>
            <ChartAreas>
                <asp:ChartArea Name="ChartArea1"></asp:ChartArea>
            </ChartAreas>
            <Legends>
                <asp:Legend Name="legend" BorderColor="Black"></asp:Legend>
            </Legends>
        </asp:Chart>
        
    </div>
   
    

</asp:Content>

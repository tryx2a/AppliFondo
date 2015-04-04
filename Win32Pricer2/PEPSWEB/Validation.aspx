<%@ Page Title="Validation" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Validation.aspx.cs" Inherits="PEPSWEB.Validation" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    
    <br><br>
    <asp:Button id="sim" Text="Simuler" ForeColor="White"  BorderStyle="Ridge" Font-Bold="true" Width="150" Height="40" runat="server" BackColor="Black" OnClick="sim_Click"/>
    <br><br>

    <div id="res">
        <br><br>
        <asp:Label id="values" Width="988px" TextMode="multiline" runat="server" />
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
                <asp:Legend Name="legend" Enabled="false" BorderColor="Black"></asp:Legend>
            </Legends>
        </asp:Chart>
    </div>
</asp:Content>


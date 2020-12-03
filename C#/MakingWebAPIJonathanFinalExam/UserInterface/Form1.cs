using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Windows.Forms;
using System.IO;
using TestAPI;
using WebApplication1.Models;
using System.Runtime.Serialization.Json;
using NwindAPI.Models;
using System.Diagnostics;

namespace UserInterface
{
    public partial class Form1 : Form
    {
        string BaseURL;
        string apiURL;
        string URL;
        List<Product> productList;

        public Form1()
        {
            InitializeComponent();
        }

        private void btnGetProduct_Click(object sender, EventArgs e)
        {
            var st = new Stopwatch();
            st.Start();
            lsProducts.Items.Clear();
            lsProducts.Items.Add("Working");
            BaseURL = txtURLSuppliers.Text + "/api/";
            apiURL = "ProductObject/" + numProductID.Value.ToString();
            URL = BaseURL + apiURL;
            Product product = new Product();
            try
            {
                for (int i = 0; i < numericUpDown1.Value; i++)
                {
                    string result = REST.HttpGet(URL); //should get one Supplier
                    DataContractJsonSerializer js = new DataContractJsonSerializer(typeof(Product));
                    byte[] byteArray = Encoding.UTF8.GetBytes(result);
                    MemoryStream ms = new MemoryStream(byteArray);
                    product = (Product)js.ReadObject(ms);
                }

                //string result = REST.HttpGet(URL); //should get one Supplier
                //DataContractJsonSerializer js = new DataContractJsonSerializer(typeof(Product));
                //byte[] byteArray = Encoding.UTF8.GetBytes(result);
                //MemoryStream ms = new MemoryStream(byteArray);
                //Product product = (Product)js.ReadObject(ms);

                //Displaying the time
                long milliseconds = st.ElapsedMilliseconds;
                lsProducts.Items.Add($"Load testing : {numericUpDown1.Value} Time to retrieve the information: {milliseconds} milliseconds");

                txtDataOut.Text = product.ProductID.ToString();
                txtProductName.Text = product.ProductName.ToString();
                txtSupplierID.Text = product.SupplierID.ToString();
                txtCategoryId.Text = product.CategoryID.ToString();
                txtQuantity.Text = product.QuantityPerUnit.ToString();
                txtUnitPrice.Text = product.UnitPrice.ToString();
                txtUnitInStock.Text = product.UnitsInStock.ToString();
                txtUnitOnOrder.Text = product.UnitsOnOrder.ToString();
                txtReorderLevel.Text = product.ReorderLevel.ToString();
                txtDiscontinued.Text = product.Discontinued.ToString();

                //lsProducts.Items.Clear();
                //lsProducts.Items.Add($"Retrieved Product = {P.ProductID} {P.ProductName} {P.CategoryID} {P.SupplierID} {P.QuantityPerUnit}");
                //MessageBox.Show(result);
            }

            catch (System.Net.WebException ex)
            {
                //can i differentiate between a web exception per se
                //vs a Supplierid not found in the database
                MessageBox.Show(ex.ToString());
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var st = new Stopwatch();
            st.Start();
            lsProducts.Items.Clear();
            lsProducts.Items.Add("Working");
            BaseURL = txtURLSuppliers.Text + "/api/";
            apiURL = "Products";
            URL = BaseURL + apiURL;
            try
            {
                for (int i = 0; i < numericUpDown1.Value; i++)
                {
                    string result = REST.HttpGet(URL); //should get one Supplier
                    DataContractJsonSerializer js = new DataContractJsonSerializer(typeof(List<Product>));
                    byte[] byteArray = Encoding.UTF8.GetBytes(result);
                    MemoryStream ms = new MemoryStream(byteArray);
                    productList = (List<Product>)js.ReadObject(ms);

                }

                //string result = REST.HttpGet(URL); //should get one Supplier
                //DataContractJsonSerializer js = new DataContractJsonSerializer(typeof(List<Product>));
                //byte[] byteArray = Encoding.UTF8.GetBytes(result);
                //MemoryStream ms = new MemoryStream(byteArray);
                //productList = (List<Product>)js.ReadObject(ms);

                long milliseconds = st.ElapsedMilliseconds;
                lsProducts.Items.Add($"Load testing : {numericUpDown1.Value} Time to retrieve the information: {milliseconds} milliseconds");
                lsProducts.Items.Add($"");
                foreach (Product tmp in productList)
                {
                    lsProducts.Items.Add($"Product ID= {tmp.ProductID} Product Name: {tmp.ProductName}");
                }


                //MessageBox.Show(result);
            }

            catch (System.Net.WebException ex)
            {
                //can i differentiate between a web exception per se
                //vs a Supplierid not found in the database
                MessageBox.Show(ex.ToString());
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void lsProducts_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lsProducts.SelectedIndex < 0)
                return;
            Product product = new Product();
            product = productList[lsProducts.SelectedIndex];

            txtDataOut.Text = product.ProductID.ToString();
            txtProductName.Text = product.ProductName.ToString();
            txtSupplierID.Text = product.SupplierID.ToString();
            txtCategoryId.Text = product.CategoryID.ToString();
            txtQuantity.Text = product.QuantityPerUnit.ToString();
            txtUnitPrice.Text = product.UnitPrice.ToString();
            txtUnitInStock.Text = product.UnitsInStock.ToString();
            txtUnitOnOrder.Text = product.UnitsOnOrder.ToString();
            txtReorderLevel.Text = product.ReorderLevel.ToString();
            txtDiscontinued.Text = product.Discontinued.ToString();

        }
    }
}

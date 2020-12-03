namespace UserInterface
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.txtURLSuppliers = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.numProductID = new System.Windows.Forms.NumericUpDown();
            this.btnGetProduct = new System.Windows.Forms.Button();
            this.lsProducts = new System.Windows.Forms.ListBox();
            this.txtDiscontinued = new System.Windows.Forms.TextBox();
            this.txtReorderLevel = new System.Windows.Forms.TextBox();
            this.txtUnitOnOrder = new System.Windows.Forms.TextBox();
            this.txtUnitInStock = new System.Windows.Forms.TextBox();
            this.txtUnitPrice = new System.Windows.Forms.TextBox();
            this.txtQuantity = new System.Windows.Forms.TextBox();
            this.txtCategoryId = new System.Windows.Forms.TextBox();
            this.txtSupplierID = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.txtProductName = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.lblProductID = new System.Windows.Forms.Label();
            this.txtDataOut = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.numProductID)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.SuspendLayout();
            // 
            // txtURLSuppliers
            // 
            this.txtURLSuppliers.Location = new System.Drawing.Point(82, 23);
            this.txtURLSuppliers.Name = "txtURLSuppliers";
            this.txtURLSuppliers.Size = new System.Drawing.Size(315, 20);
            this.txtURLSuppliers.TabIndex = 3;
            this.txtURLSuppliers.Text = "http://localhost:63490";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(17, 26);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Base URL:";
            // 
            // numProductID
            // 
            this.numProductID.Location = new System.Drawing.Point(227, 148);
            this.numProductID.Maximum = new decimal(new int[] {
            1410065407,
            2,
            0,
            0});
            this.numProductID.Name = "numProductID";
            this.numProductID.Size = new System.Drawing.Size(63, 20);
            this.numProductID.TabIndex = 11;
            this.numProductID.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // btnGetProduct
            // 
            this.btnGetProduct.Location = new System.Drawing.Point(94, 140);
            this.btnGetProduct.Margin = new System.Windows.Forms.Padding(4);
            this.btnGetProduct.Name = "btnGetProduct";
            this.btnGetProduct.Size = new System.Drawing.Size(126, 32);
            this.btnGetProduct.TabIndex = 10;
            this.btnGetProduct.Text = "Get Product";
            this.btnGetProduct.UseVisualStyleBackColor = true;
            this.btnGetProduct.Click += new System.EventHandler(this.btnGetProduct_Click);
            // 
            // lsProducts
            // 
            this.lsProducts.FormattingEnabled = true;
            this.lsProducts.Location = new System.Drawing.Point(406, 162);
            this.lsProducts.Margin = new System.Windows.Forms.Padding(4);
            this.lsProducts.Name = "lsProducts";
            this.lsProducts.Size = new System.Drawing.Size(521, 407);
            this.lsProducts.TabIndex = 9;
            this.lsProducts.SelectedIndexChanged += new System.EventHandler(this.lsProducts_SelectedIndexChanged);
            // 
            // txtDiscontinued
            // 
            this.txtDiscontinued.Location = new System.Drawing.Point(113, 432);
            this.txtDiscontinued.Name = "txtDiscontinued";
            this.txtDiscontinued.ReadOnly = true;
            this.txtDiscontinued.Size = new System.Drawing.Size(170, 20);
            this.txtDiscontinued.TabIndex = 51;
            // 
            // txtReorderLevel
            // 
            this.txtReorderLevel.Location = new System.Drawing.Point(113, 406);
            this.txtReorderLevel.Name = "txtReorderLevel";
            this.txtReorderLevel.ReadOnly = true;
            this.txtReorderLevel.Size = new System.Drawing.Size(170, 20);
            this.txtReorderLevel.TabIndex = 50;
            // 
            // txtUnitOnOrder
            // 
            this.txtUnitOnOrder.Location = new System.Drawing.Point(113, 380);
            this.txtUnitOnOrder.Name = "txtUnitOnOrder";
            this.txtUnitOnOrder.ReadOnly = true;
            this.txtUnitOnOrder.Size = new System.Drawing.Size(170, 20);
            this.txtUnitOnOrder.TabIndex = 49;
            // 
            // txtUnitInStock
            // 
            this.txtUnitInStock.Location = new System.Drawing.Point(113, 354);
            this.txtUnitInStock.Name = "txtUnitInStock";
            this.txtUnitInStock.ReadOnly = true;
            this.txtUnitInStock.Size = new System.Drawing.Size(170, 20);
            this.txtUnitInStock.TabIndex = 48;
            // 
            // txtUnitPrice
            // 
            this.txtUnitPrice.Location = new System.Drawing.Point(94, 328);
            this.txtUnitPrice.Name = "txtUnitPrice";
            this.txtUnitPrice.ReadOnly = true;
            this.txtUnitPrice.Size = new System.Drawing.Size(170, 20);
            this.txtUnitPrice.TabIndex = 47;
            // 
            // txtQuantity
            // 
            this.txtQuantity.Location = new System.Drawing.Point(131, 302);
            this.txtQuantity.Name = "txtQuantity";
            this.txtQuantity.ReadOnly = true;
            this.txtQuantity.Size = new System.Drawing.Size(170, 20);
            this.txtQuantity.TabIndex = 46;
            // 
            // txtCategoryId
            // 
            this.txtCategoryId.Location = new System.Drawing.Point(102, 276);
            this.txtCategoryId.Name = "txtCategoryId";
            this.txtCategoryId.ReadOnly = true;
            this.txtCategoryId.Size = new System.Drawing.Size(170, 20);
            this.txtCategoryId.TabIndex = 45;
            // 
            // txtSupplierID
            // 
            this.txtSupplierID.Location = new System.Drawing.Point(102, 250);
            this.txtSupplierID.Name = "txtSupplierID";
            this.txtSupplierID.ReadOnly = true;
            this.txtSupplierID.Size = new System.Drawing.Size(170, 20);
            this.txtSupplierID.TabIndex = 44;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(35, 439);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(72, 13);
            this.label11.TabIndex = 43;
            this.label11.Text = "Discontinued:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(35, 413);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(77, 13);
            this.label10.TabIndex = 42;
            this.label10.Text = "Reorder Level:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(35, 387);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(75, 13);
            this.label9.TabIndex = 41;
            this.label9.Text = "Unit On Order:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(35, 361);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(72, 13);
            this.label8.TabIndex = 40;
            this.label8.Text = "Unit In Stock:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(35, 335);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(56, 13);
            this.label7.TabIndex = 39;
            this.label7.Text = "Unit Price:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(35, 309);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(90, 13);
            this.label6.TabIndex = 38;
            this.label6.Text = "Quantity Per Unit:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(35, 283);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(63, 13);
            this.label5.TabIndex = 37;
            this.label5.Text = "Categoy ID:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(35, 257);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(62, 13);
            this.label4.TabIndex = 36;
            this.label4.Text = "Supplier ID:";
            // 
            // txtProductName
            // 
            this.txtProductName.Location = new System.Drawing.Point(117, 224);
            this.txtProductName.Name = "txtProductName";
            this.txtProductName.ReadOnly = true;
            this.txtProductName.Size = new System.Drawing.Size(170, 20);
            this.txtProductName.TabIndex = 35;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(35, 231);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(78, 13);
            this.label3.TabIndex = 34;
            this.label3.Text = "Product Name:";
            // 
            // lblProductID
            // 
            this.lblProductID.AutoSize = true;
            this.lblProductID.Location = new System.Drawing.Point(35, 206);
            this.lblProductID.Name = "lblProductID";
            this.lblProductID.Size = new System.Drawing.Size(61, 13);
            this.lblProductID.TabIndex = 33;
            this.lblProductID.Text = "Product ID:";
            // 
            // txtDataOut
            // 
            this.txtDataOut.Location = new System.Drawing.Point(102, 199);
            this.txtDataOut.Name = "txtDataOut";
            this.txtDataOut.ReadOnly = true;
            this.txtDataOut.Size = new System.Drawing.Size(187, 20);
            this.txtDataOut.TabIndex = 32;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(572, 122);
            this.button1.Margin = new System.Windows.Forms.Padding(4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(126, 32);
            this.button1.TabIndex = 52;
            this.button1.Text = "Get List of Products";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Arial Black", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(216, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(221, 41);
            this.label2.TabIndex = 53;
            this.label2.Text = "Load Testing";
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Font = new System.Drawing.Font("Arial Black", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.numericUpDown1.Location = new System.Drawing.Point(443, 56);
            this.numericUpDown1.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.numericUpDown1.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(164, 48);
            this.numericUpDown1.TabIndex = 54;
            this.numericUpDown1.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(940, 582);
            this.Controls.Add(this.numericUpDown1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.txtDiscontinued);
            this.Controls.Add(this.txtReorderLevel);
            this.Controls.Add(this.txtUnitOnOrder);
            this.Controls.Add(this.txtUnitInStock);
            this.Controls.Add(this.txtUnitPrice);
            this.Controls.Add(this.txtQuantity);
            this.Controls.Add(this.txtCategoryId);
            this.Controls.Add(this.txtSupplierID);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txtProductName);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lblProductID);
            this.Controls.Add(this.txtDataOut);
            this.Controls.Add(this.numProductID);
            this.Controls.Add(this.btnGetProduct);
            this.Controls.Add(this.lsProducts);
            this.Controls.Add(this.txtURLSuppliers);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Jonathan Program";
            ((System.ComponentModel.ISupportInitialize)(this.numProductID)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtURLSuppliers;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numProductID;
        private System.Windows.Forms.Button btnGetProduct;
        private System.Windows.Forms.ListBox lsProducts;
        private System.Windows.Forms.TextBox txtDiscontinued;
        private System.Windows.Forms.TextBox txtReorderLevel;
        private System.Windows.Forms.TextBox txtUnitOnOrder;
        private System.Windows.Forms.TextBox txtUnitInStock;
        private System.Windows.Forms.TextBox txtUnitPrice;
        private System.Windows.Forms.TextBox txtQuantity;
        private System.Windows.Forms.TextBox txtCategoryId;
        private System.Windows.Forms.TextBox txtSupplierID;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtProductName;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label lblProductID;
        private System.Windows.Forms.TextBox txtDataOut;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
    }
}


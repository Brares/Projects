using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using NwindAPI.Models;
using NwindAPI.BusinessLayer;

namespace NwindAPI.Controllers
{
    public class ProductController : ApiController
    {
        [HttpGet]
        [Route("api/Products")]
        public IEnumerable<Product> GetProducts()
        {
            List<Product> ProductList = BLProduct.ProductList();

            return ProductList;
        }

        [HttpGet]
        [Route("api/ProductPrice/{ProductID:int}")]
        public IHttpActionResult GetProductPrice(int ProductID)
        {
            Product P = BLProduct.GetProduct(ProductID);
            if (P != null)
            {
                return Ok(P.UnitPrice);
            }
            else //Supplierid not found
            {
                return NotFound();
            }
        }

        [HttpGet]
        [Route("api/ProductObject/{ProductID:int}")]
        public IHttpActionResult GetProduct(int ProductID)
        {
            Product P = BLProduct.GetProduct(ProductID);
            if (P != null)
            {
                return Ok(P);
            }
            else //Supplierid not found
            {
                return NotFound();
            }
        }
    }
}
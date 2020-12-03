using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using WebApplication1.Models;
namespace WebApplication1.Controllers
{
    public class ShippersController : ApiController
    {
        // GET api/<controller>  use attribute routing instead:
        //[HttpGet]
        //[Route("api/shippers")]
        public List<Shipper> Get()
        {
            return Shipper.TestList();
        }

         [HttpGet]
        [Route("api/shippers/{ShipperID:int}")]
        public IHttpActionResult GetShipper(int ShipperID)
        {
            if (ShipperID <=3)
            { 
            //"go to database" and get shipper for id requested
            Shipper testShipper = new Shipper();
            testShipper.ShipperID = ShipperID;
            testShipper.CompanyName = "S" + ShipperID.ToString();
            testShipper.Phone = "test phone";
            return Ok(testShipper);
            }
            else
            {
                return Content(HttpStatusCode.BadRequest, "Shipper ID " + ShipperID.ToString() + " does not exist");
            }
        }

        //get a shipper phone
        //http:xxxx/api/shippers/phone/3
        [HttpGet]
        [Route("api/shippers/phone/{ShipperID:int}")]
        public IHttpActionResult GetShipperPhone(int ShipperID)
        {
            if (ShipperID <= 3)
            {
                //"go to database" and get shipper phone for id requested
                string phone = ShipperID.ToString().PadLeft(9, ShipperID.ToString()[0]);
                    return Ok(phone);
            }
            else
            {

                return Content(HttpStatusCode.BadRequest, "Shipper ID " + ShipperID.ToString() + " does not exist");

            }
        }




        //add new shipper
        [HttpPost]
        [Route("api/shippers")]
        public IHttpActionResult AddNewShipper(Shipper NewShipper)
        {
            try
            {
                //int NewShipperID = BL.AddNewShipper(NewShipper);
                int NewShipperID = 4;
                return Ok(NewShipperID);
            }
            catch (Exception ex)
            {
                //what to do with errors?
                // HttpError err = new HttpError("A shipper named " + NewShipper.CompanyName + " already exists.");
                //HttpResponseMessage hrm = Request.CreateResponse(HttpStatusCode.NotFound, err);
                //return (IHttpActionResult) hrm; //still gives 500 internal server error on the client and no message
                return Content(HttpStatusCode.BadRequest, "A shipper named " + NewShipper.CompanyName + " already exists.");
            }

        }

        //change shipper phone through URL values
        [HttpPatch]
        [Route("api/shippers/ChangePhone/{ShipperID:int}/{NewPhone}")]
        public IHttpActionResult ChangeShipperPhone(int ShipperID, string NewPhone)
        {
            try
            {
                //BL.ChangeShipperPhone(ShipperID, NewPhone);
                return Ok();
            }
            catch (Exception ex)
            {
                //what to do with errors?
                return Content(HttpStatusCode.BadRequest, ex.Message);

            }

        }

  


    }
}
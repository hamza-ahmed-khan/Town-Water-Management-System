import React, { useState, useEffect } from "react";
import { Grid } from "@material-ui/core";
import MUIDataTable from "mui-datatables";

// components
import PageTitle from "../../components/PageTitle";

const Receipt = () => {
  const [receiptData, setReceiptData] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    fetch('https://backend-eta-neon.vercel.app/receipt')
      .then((response) => response.json())
      .then((data) => {
        setReceiptData(data);
        setLoading(false);
      })
      .catch((error) => {
        setError(error);
        setLoading(false);
      });
  }, []);

  if (loading) {
    return <div>Loading...</div>;
  }

  if (error) {
    return <div>Error: {error.message}</div>;
  }

  if (!receiptData) {
    return <div>No data available</div>;
  }

  const datatableData = [
    [receiptData.house_a.username, receiptData.house_a.time, receiptData.house_a.house_id, receiptData.house_a.bill_amount],
    ["Aneeqa Fahim", "72-B", "A", "1100"],
  ];

  return (
    <>
      <PageTitle title="Bill Generation" />
      <Grid container spacing={4}>
        <Grid item xs={12}>
          <MUIDataTable
            title="Registered Houses List"
            data={datatableData}
            columns={["Owner Name", "House Number", "Block Number", "Total Bill"]}
            options={{
              filterType: "checkbox",
            }}
          />
        </Grid>
      </Grid>
    </>
  );
};

export default Receipt;

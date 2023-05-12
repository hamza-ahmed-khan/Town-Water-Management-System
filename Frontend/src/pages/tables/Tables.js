import React from "react";
import { Grid } from "@material-ui/core";
import MUIDataTable from "mui-datatables";

// components
import PageTitle from "../../components/PageTitle";

const datatableData = [
  ["Aliza Shafiq", "72-A", "A","900"],
  ["Aneeqa Fahim", "72-B", "A","1100"],
]

export default function Tables() {
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
}

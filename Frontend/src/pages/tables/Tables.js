import React from "react";
import { Grid } from "@material-ui/core";
import { makeStyles } from "@material-ui/styles";
import MUIDataTable from "mui-datatables";

// components
import PageTitle from "../../components/PageTitle";
import Widget from "../../components/Widget";
import Table from "../dashboard/components/Table/Table";

// data
import mock from "../dashboard/mock";

const datatableData = [
  ["Aliza Shafiq", "72-A", "A","900"],
  ["Aneeqa Fahim", "72-B", "A","1100"],
]

const useStyles = makeStyles(theme => ({
  tableOverflow: {
    overflow: 'auto'
  }
}))

export default function Tables() {
  const classes = useStyles();
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

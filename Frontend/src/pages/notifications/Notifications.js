import React from "react";
import { Grid } from "@material-ui/core";

// styles
import "react-toastify/dist/ReactToastify.css";

// components
import Widget from "../../components/Widget/Widget";
import PageTitle from "../../components/PageTitle/PageTitle";
import Table from "../dashboard/components/Table/Table";

// data
import mock from "../dashboard/mock";


export default function NotificationsPage(props) {
  



  return (
    <div>
      {" "}
      <PageTitle title="Bill Tracking" />
      <Grid container spacing={4}>
        <Grid item xs={12}>
          <Widget title="Bill Tracking">
            <Table data={mock.table} />
          </Widget>
        </Grid>
      </Grid>
    </div>
  );
}

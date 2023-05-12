import React, { useState, useEffect } from "react";
import axios from "axios";
// styles
import {
  Grid,
  Button,
} from "@material-ui/core";
import Widget from "../../components/Widget";
import PageTitle from "../../components/PageTitle";

export default function WaterFlowControl() {
  const [isFlowing, setIsFlowing] = useState(true);
  const [isMotorOn, setisMotorOn] = useState(true);
  const [isFlowinghouse, setisFlowinghouse] = useState(true);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get(
          `https://twmsdeploy.azurewebsites.net/ValveStatus?isFlowing=${isFlowing}`,
        );
        console.log(response.data);
      } catch (error) {
        console.error(error);
      }
    };

    fetchData();
  }, [isFlowing]);

  const toggleWaterFlow = () => {
    setIsFlowing((prevState) => !prevState);
  };
  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get(
          `https://twmsdeploy.azurewebsites.net/HouseValveStatus?isFlowinghouse=${isFlowinghouse}`,
        );
        console.log(response.data);
      } catch (error) {
        console.error(error);
      }
    };

    fetchData();
  }, [isFlowinghouse]);

  const toggleWaterFlowhouse = () => {
    setisFlowinghouse((prevState) => !prevState);
  };
  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get(
          `https://twmsdeploy.azurewebsites.net/PumpStatus?isMotorOn=${isMotorOn}`,
        );
        console.log(response.data);
      } catch (error) {
        console.error(error);
      }
    };

    fetchData();
  }, [isMotorOn]);

  const toggleMotor = () => {
    setisMotorOn((prevState) => !prevState);
  };

  return (
    <div>
      <PageTitle title="Control Center"></PageTitle>
      <Grid container spacing={4} alignItems="center" justify="center">
        <Grid item lg={10} md={8} sm={12} xs={12}>
          <Widget title="Block A" style={{ textAlign: "center",titleAlign:"center" }}>
            <Grid container item alignItems="center" justify="center">
              <Grid item xs={6}>
                <h3 style={{ textAlign: "center" }}>Motor Status</h3>
              </Grid>
              <Grid item xs={6}>
                <Button
                  onClick={toggleMotor}
                  variant="contained"
                  size="medium"
                  color="primary"
                >
                  {isMotorOn ? "OFF" : "ON"}
                </Button>
              </Grid>
            </Grid>
          </Widget>
        </Grid>
      </Grid>

      <Grid container spacing={4} alignItems="center" justify="center">
        <Grid item lg={4} md={8} sm={12} xs={12}>
          <Widget title="House Number 1">
            <Grid container item alignItems={"center"}>
              <Grid item xs={6}>
                <h3 style={{ textAlign: "center" }}>Valve Status</h3>
              </Grid>
              <Grid item xs={6}>
                <Button
                  onClick={toggleWaterFlow}
                  variant="contained"
                  size="small"
                  color="primary"
                >
                  {isFlowing ? "OFF" : "ON"}
                </Button>
              </Grid>
            </Grid>
          </Widget>
        </Grid>
        <Grid item lg={4} md={8} sm={12} xs={12}>
          <Widget title="House Number 2">
            <Grid container item alignItems={"center"}>
              <Grid item xs={6}>
                <h3 style={{ textAlign: "center" }}>Valve Status</h3>
              </Grid>
              <Grid item xs={6}>
                <Button
                  onClick={toggleWaterFlowhouse}
                  variant="contained"
                  size="small"
                  color="primary"
                >
                  {isFlowinghouse ? "OFF" : "ON"}
                </Button>
              </Grid>
            </Grid>
          </Widget>
        </Grid>
      </Grid>


    </div>
  );
}

import React, { useState, useEffect } from 'react';
import axios from 'axios';

export default function WaterFlowControl() {
  const [isFlowing, setIsFlowing] = useState(true);
  const [isMotorOn, setisMotorOn] = useState(true);
  const [isFlowinghouse, setisFlowinghouse] = useState(true);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get(`http://localhost:5000/ValveStatus?isFlowing=${isFlowing}`);
        console.log(response.data);
      } catch (error) {
        console.error(error);
      }
    };

    fetchData();
  }, [isFlowing]);
  
  const toggleWaterFlow = () => {
    setIsFlowing(prevState => !prevState);
  };
  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get(`http://localhost:5000/ValveStatus?isFlowinghouse=${isFlowinghouse}`);
        console.log(response.data);
      } catch (error) {
        console.error(error);
      }
    };

    fetchData();
  }, [isFlowinghouse]);
  
  const toggleWaterFlowhouse = () => {
    setisFlowinghouse(prevState => !prevState);
  };
  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get(`http://localhost:5000/ValveStatus?isMotorOn=${isMotorOn}`);
        console.log(response.data);
      } catch (error) {
        console.error(error);
      }
    };

    fetchData();
  }, [isMotorOn]);
  
  const toggleMotor = () => {
    setisMotorOn(prevState => !prevState);
  };

  return (
    <div>
      <h2>House 1 Valve</h2>
      <button onClick={toggleWaterFlow}>{isFlowing ? 'OFF' : 'ON'}</button>
      <h2>PUMP</h2>
      <button onClick={toggleMotor}>{isMotorOn ? 'OFF' : 'ON'}</button>
      <h2>House 2 Valve</h2>
      <button onClick={toggleWaterFlowhouse}>{isFlowinghouse ? 'OFF' : 'ON'}</button>
    </div>
    
        
      
  );
};

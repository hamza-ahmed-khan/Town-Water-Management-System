import React, { useState, useEffect } from 'react';
import axios from 'axios';

export default function WaterFlowControl() {
  const [isFlowing, setIsFlowing] = useState(true);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get(`https://hamza19b.pythonanywhere.com/ValveStatus?isFlowing=${isFlowing}`);
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

  return (
    <div>
      <button onClick={toggleWaterFlow}>{isFlowing ? 'OFF' : 'ON'}</button>
    </div>
  );
};

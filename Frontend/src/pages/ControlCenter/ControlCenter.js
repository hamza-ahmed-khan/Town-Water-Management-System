import React, { useState } from 'react';

function WaterFlowControl() {
  const [isFlowing, setIsFlowing] = useState(false);

  const handleToggleFlow = async () => {
    try {
      const response = await fetch('/api/water-flow-control', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({ isFlowing: !isFlowing })
      });
      if (response.ok) {
        setIsFlowing(!isFlowing);
      }
    } catch (error) {
      console.error(error);
    }
  };

  return (
    <div>
      <button onClick={handleToggleFlow}>{isFlowing ? 'OFF' : 'ON'}</button>
    </div>
  );
}

export default WaterFlowControl;
const mock = {
  tasks: [
    {
      id: 0,
      type: "Mantainance",
      title: "Ultrasonic Sensor Issue",
      time: "9:00",
      Address:"72-B"
    },
    {
      id: 1,
      type: "Installation",
      title: "NodeMCU wifi module",
      time: "12:00",
      Address:"72-A"
    },
  ],
  bigStat: [
    {
      product: "Block A",
      total: {
        monthly: 4232,
        weekly: 1465,
        daily: 199,
        percent: { value: 3.7, profit: false }
      },
      color: "primary",
      registrations: {
        monthly: { value: 830, profit: false },
        weekly: { value: 215, profit: true },
        daily: { value: 33, profit: true }
      },
      bounce: {
        monthly: { value: 4.5, profit: false },
        weekly: { value: 3, profit: true },
        daily: { value: 3.25, profit: true }
      }
    },
    {
      product: "Block B",
      total: {
        monthly: 754,
        weekly: 180,
        daily: 27,
        percent: { value: 2.5, profit: true }
      },
      color: "warning",
      registrations: {
        monthly: { value: 32, profit: true },
        weekly: { value: 8, profit: true },
        daily: { value: 2, profit: false }
      },
      bounce: {
        monthly: { value: 2.5, profit: true },
        weekly: { value: 4, profit: false },
        daily: { value: 4.5, profit: false }
      }
    },
    {
      product: "Block C",
      total: {
        monthly: 1025,
        weekly: 301,
        daily: 44,
        percent: { value: 3.1, profit: true }
      },
      color: "secondary",
      registrations: {
        monthly: { value: 230, profit: true },
        weekly: { value: 58, profit: false },
        daily: { value: 15, profit: false }
      },
      bounce: {
        monthly: { value: 21.5, profit: false },
        weekly: { value: 19.35, profit: false },
        daily: { value: 10.1, profit: true }
      }
    }
  ],
  notifications: [
    {
      id: 0,
      icon: "thumbs-up",
      color: "primary",
      content:
        'Ken <span className="fw-semi-bold">accepts</span> your invitation'
    },
    {
      id: 1,
      icon: "file",
      color: "success",
      content: "Report from LT Company"
    },
    {
      id: 2,
      icon: "envelope",
      color: "danger",
      content: '4 <span className="fw-semi-bold">Private</span> Mails'
    },
    {
      id: 3,
      icon: "comment",
      color: "success",
      content: '3 <span className="fw-semi-bold">Comments</span> to your Post'
    },
    {
      id: 4,
      icon: "cog",
      color: "light",
      content: 'New <span className="fw-semi-bold">Version</span> of RNS app'
    },
    {
      id: 5,
      icon: "bell",
      color: "info",
      content:
        '15 <span className="fw-semi-bold">Notifications</span> from Social Apps'
    }
  ],
  table: [
    {
      id: 0,
      name: "Hamza Ahmed Khan",
      email: "hamza@gmail.com",
      address: "95-G",
      block: "B",
      date: "19 May 2023",
      bill:"1600",
      status: "Sent"
    },
    {
      id: 1,
      name: "Hamza Qadri",
      email: "qadri154@gmail.com",
      address: "73-C",
      block: "A",
      date: "14 May 2023",
      bill:"1200",
      status: "Pending"
    },
    {
      id: 3,
      name: "Aneeqa Fahim",
      email: "anfahim@gmail.com",
      address: "72-B",
      block: "A",
      date: "04 Jun 2023",
      bill:"1100",
      status: "Not Sent"
    }
    
  ]
};

export default mock;
<?php
$val = 0;
// If form submitted, insert values into the database.
if (isset($_POST['uname'])) {

  $uname = $_REQUEST['uname'];
  $pass = $_REQUEST['pass'];
  if ($uname == "admin" && $pass == "admin") {
    header("Location: assign.php");
  } elseif ($uname == "sanjanasw" && $pass == "nova1223") {
    header("Location: live.html");
  } else {
    $val = 1;
  }
}
?>
<html>

<head>
  <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
  <meta charset="utf-8">
  <meta content="width=device-width, initial-scale=1.0" name="viewport">

  <title>my page</title>
  <meta content="" name="description">
  <meta content="" name="keywords">

  <!-- Favicons -->
  <!--<link href="assets/img/favicon.png" rel="icon">
        <link href="assets/img/apple-touch-icon.png" rel="apple-touch-icon"> -->

  <!-- Google Fonts -->
  <link href="https://fonts.googleapis.com/css?family=Open+Sans:300,300i,400,400i,600,600i,700,700i|Raleway:300,300i,400,400i,500,500i,600,600i,700,700i|Poppins:300,300i,400,400i,500,500i,600,600i,700,700i" rel="stylesheet">

  <!-- Vendor CSS Files -->
  <link href="assets/vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
  <link href="assets/vendor/icofont/icofont.min.css" rel="stylesheet">
  <link href="assets/vendor/boxicons/css/boxicons.min.css" rel="stylesheet">
  <link href="assets/vendor/venobox/venobox.css" rel="stylesheet">
  <link href="assets/vendor/owl.carousel/assets/owl.carousel.min.css" rel="stylesheet">
  <link href="assets/vendor/aos/aos.css" rel="stylesheet">
  <script src="https://cdn.jsdelivr.net/npm/sweetalert2@10.16.6/dist/sweetalert2.all.min.js"></script>

  <!-- Template Main CSS File -->
  <link href="assets/css/style.css" rel="stylesheet">


  <!---- <style>
            body {
              background-image: url('cta-bg.jpg');
              background-repeat: no-repeat;
              background-attachment: fixed;  
              background-size: cover;
            }
            </style> -->


</head>

<body>


  <header id="header" class="fixed-top ">
    <div class="container d-flex align-items-center">

      <h2 class="logo mr-auto"><a href="index.php">NOVA</a></h2>


      <nav class="nav-menu d-none d-lg-block">
        <ul>
          <li><a href="index.php">Home</a></li>
          <li class="active"><a href="#">Login</a></li>
        </ul>
      </nav><!-- .nav-menu -->

    </div>
  </header>
  <section id="hero" class="d-flex align-items-center">
    <div class="container position-relative" data-aos="fade-up" data-aos-delay="500">
      <form class="container" class="align-middle" action="" method="post">

        <div class="form-group col-md-4">
          <label class="text-white" for="inputEmail4">User Name</label>
          <input type="text" class="form-control" id="inputEmail4" placeholder="User Name" name="uname">
        </div>
        <div class="form-group col-md-4">
          <label class="text-white" for="inputPassword4">Password</label>
          <input type="password" class="form-control" id="inputPassword4" placeholder="Password" name="pass">
        </div>

        <div>
          <input type="submit" value="Login" class="btn btn-primary">
        </div>




      </form>

    </div>
    <?php
    if ($val == 1) {
    ?>

      <script>
        Swal.fire({
          icon: 'error',
          title: 'ERROR',
          text: 'Account Not Found!!'
        })
      </script>
    <?php } ?>
  </section>
  </div>

  <div id="preloader"></div>
  <script src="assets/vendor/jquery/jquery.min.js"></script>
  <script src="assets/vendor/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="assets/vendor/jquery.easing/jquery.easing.min.js"></script>
  <script src="assets/vendor/php-email-form/validate.js"></script>
  <script src="assets/vendor/isotope-layout/isotope.pkgd.min.js"></script>
  <script src="assets/vendor/venobox/venobox.min.js"></script>
  <script src="assets/vendor/owl.carousel/owl.carousel.min.js"></script>
  <script src="assets/vendor/aos/aos.js"></script>

  <script src="assets/js/main.js"></script>


</body>

</html>
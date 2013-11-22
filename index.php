<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html lang="en" xml:lang="en" xmlns="http://www.w3.org/1999/xhtml">
<head>
  	<title>Brain Computer Interface</title>
  	<meta content="text/html; charset=utf-8" http-equiv="content-type" />
  	<meta name="viewport" content="width=device-width, initial-scale=1.0">
  	<!-- Bootstrap -->
  	<link href="assets/css/bootstrap.min.css" rel="stylesheet" media="screen">
  	<!-- Custom Styles -->
  	<link href="assets/css/styles.css" rel="stylesheet" media="screen">
  	<script src='assets/js/jquery.js'></script>
  	<script src='assets/js/bootstrap.min.js'></script>
    <script>
      function toggleUI()
      {
        if(document.getElementById('optionsRadios1').checked)
        {
          document.getElementById('classLabelDiv').style.display="";
          document.getElementById('submitButton').innerHTML='Begin Training';
        }
        else
        {
          document.getElementById('classLabelDiv').style.display="none";
          document.getElementById('submitButton').innerHTML='Begin the Test';
        }
      }

      function validate()
      {
        if(document.getElementById('optionsRadios1').checked)
          if(document.getElementById('classLabel').value == "")
          {
            alert("Classification Label field is empty.");
            return false;
          }
          return true;
      }
    </script>
  </head>
  <body style="background-color:#2277bb;">
    <?php require_once("navbar.php"); ?>
    <div class='jumbotron'>
      <h1>EEG based BCI <br><small><br>A Brain Computer Interface utilizing EEG signals from a neuroheadset</small></h1>
      <button class='btn btn-danger'><span class='glyphicon glyphicon-save'></span> Download Source</button>
      <button class='btn btn-info'><span class='glyphicon glyphicon-info-sign'></span> About</button>
    </div>
    <div class='well container' align='center'>
    <form>
      <table class='table' style='width:80%;'>
        <tr>
          <td align='center'>
            <h1><small>
              <div class="radio-inline">
                <label>
                  <input type="radio" name="optionsRadios" id="optionsRadios1" value="option1" onclick='toggleUI();' checked>
                    Training &mdash; Induce the model
                </label>
              </div>
            <small></h1>
          </td>
          <td align='center'>
            <h1><small>
              <div class="radio-inline">
                <label>
                  <input type="radio" name="optionsRadios" id="optionsRadios2" onclick='toggleUI();' value="option2">
                    Test &mdash; Deduce the class
                </label>
              </div>
            </small></h1>
          </td>
        </tr>
      </table>
      <div id='classLabelDiv'>
        <h3>Enter classification label</h3>
        <input type='text' style='width:50%;' class='form-control' id='classLabel' name='classLabel' autofocus>
      </div>
      <hr>
      <button class='btn btn-success btn-lg btn-block' id='submitButton' style='width:50%' onclick='validate();'> Begin Training </button>
    </form>
  </device-widthv>
  </body>
</html> 
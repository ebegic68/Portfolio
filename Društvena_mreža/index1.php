<?php include "inc/header.php" ?>

<?php
if(isset($_SESSION['email'])) : ?>
<?php create_post(); ?>
<br>
<form method="POST">
<h3>Create new post</h3>
<textarea name="post_content" id="" cols="60" rows="11" placeholder="Post content..."></textarea>
<input type="submit" value="Post" name="submit">
</form>
<div>
    <?php display_message(); ?>
</div>
<hr>

<div class="posts">
  <?php fetch_all_posts() ?>
</div>
   
<?php else: ?>
    <div class="homepage">
        <h1>Welcome to Social Network</h1>
        <p>You must register before proceeding if you do not already have a profile created!</p>
        <h2>Click <a href="login.php">here</a> to login!</h2>
        <img src="css/img/download.jpg" alt="">
</div>
    

<?php endif; ?>
<?php include "inc/footer.php";
